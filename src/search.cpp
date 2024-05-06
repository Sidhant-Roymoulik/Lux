#include "search.h"

#include "eval.h"
#include "history.h"
#include "move_score.h"
#include "pv.h"

// Late-Move Precomputations
int LMR_TABLE[MAX_PLY][constants::MAX_MOVES];

void init_search_tables() {
    for (int depth = 1; depth < MAX_PLY; depth++) {
        for (int move = 1; move < 256; move++) {
            LMR_TABLE[depth][move] = 2 + log(depth) * log(move) / 2.5;
        }
    }
}

// Explicit template instantiation
template void iterative_deepening<false>(SearchThread& st);
template void iterative_deepening<true>(SearchThread& st);

template <bool print_info>
void iterative_deepening(SearchThread& st) {
    SearchInfo& info = st.info;

    st.clear();
    st.initialize();

    int score = 0;

    auto start_time = st.start_time();
    Move bestmove   = Move::NO_MOVE;

    for (int current_depth = 1; current_depth < info.depth; current_depth++) {
        score = aspiration_window(score, current_depth, st);

        if (st.info.stopped || st.stop_early()) break;

        bestmove   = st.bestmove;
        info.score = score;

        if (st.info.time_set) st.tm.update_tm(bestmove);

        if constexpr (print_info) {
            if (info.print_uci) {
                auto time_elapsed = now() - start_time;

                std::cout << "info"
                          << " depth " << current_depth << " score ";

                if (score >= -MATE && score <= MATED_IN_MAX) {
                    std::cout << "mate " << ((-MATE - score) / 2);
                } else if (score <= MATE && score >= MATE_IN_MAX) {
                    std::cout << "mate " << ((MATE - score) / 2);
                } else {
                    std::cout << "cp " << score;
                }

                std::cout << " nodes " << st.nodes << " nps "
                          << static_cast<int>(1000.0f * st.nodes / (time_elapsed + 1)) << " time "
                          << static_cast<uint64_t>(time_elapsed) << " pv";

                std::vector<uint64_t> positions;
                get_pv(st, positions, bestmove);

                std::cout << std::endl;
            } else {
                auto time_elapsed = now() - start_time;

                printf("[%2d/%2d] > eval: %-4.2f nodes: %6.2fM speed: %-5.2f MNPS", current_depth, info.depth,
                       static_cast<float>(score / 100.0f), static_cast<float>(st.nodes / 1000000.0f),
                       static_cast<float>(1000.0f * st.nodes / (time_elapsed + 1)) / 1000000.0f);

                std::vector<uint64_t> positions;
                get_pv(st, positions, bestmove);

                std::cout << std::endl;
            }
        }
    }

    if (print_info) {
        std::cout << "bestmove " << uci::moveToUci(bestmove) << std::endl;
    }
}

int aspiration_window(int prev, int depth, SearchThread& st) {
    SearchStack stack[MAX_PLY + 10], *ss = stack + 7;

    int delta = 10 + prev * prev / 16000;
    int alpha = std::max(prev - delta, -MATE);
    int beta  = std::min(prev + delta, static_cast<int>(MATE));

    int score = 0;
    while (true) {
        score = negamax(st, ss, alpha, beta, depth, false);

        if (score <= alpha) {
            beta  = (alpha + beta) / 2;
            alpha = std::max(score - delta, -MATE);

        } else if (score >= beta) {
            beta = std::min(score + delta, static_cast<int>(MATE));

        } else
            break;

        delta += delta / 3;
    }

    return score;
}

int negamax(SearchThread& st, SearchStack* ss, int alpha, int beta, int depth, bool cutnode) {
    // Increment total nodes
    st.nodes++;

    // Check for time up every 2048 nodes
    if ((st.nodes & 2047) == 0) st.check_time();
    // Exit search if time over
    if (st.info.stopped) return 0;

    bool root    = (ss->ply == 0);
    bool pv_node = beta - alpha > 1;

    if (!root) {
        // Check for draw by repetition && draw by 50-move rule
        if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return 0;

        // Ply cap to prevent endless search
        if (ss->ply >= MAX_PLY) return evaluate(st.board);

        // Mate Distance Pruning
        alpha = std::max(alpha, -MATE + ss->ply);
        beta  = std::min(beta, MATE - ss->ply - 1);
        if (alpha >= beta) return alpha;
    }

    bool in_check = st.board.inCheck();

    // Check Extensions
    if (in_check) depth++;

    // If you reach 0-depth drop into q-search
    if (depth <= 0) {
        st.nodes--;
        return q_search(st, ss, alpha, beta);
    }

    // Probe Transposition Table
    bool tt_hit  = false;
    TTEntry& tte = table->probe_entry(st.board.hash(), tt_hit);
    Move tt_move = Move::NO_MOVE;

    if (tt_hit) {
        tt_move      = tte.move;
        int tt_score = score_from_tt(tte.score, ss->ply);
        if (!pv_node && tte.depth >= depth && (tte.flag & (tt_score >= beta ? FLAG_BETA : FLAG_ALPHA))) return tt_score;
    }

    ss->static_eval = tt_hit ? tte.eval : evaluate(st.board);
    bool improving  = !in_check && ss->static_eval > (ss - 2)->static_eval;

    // Various Pruning Methods
    if (pv_node || in_check || (ss - 1)->move == Move::NULL_MOVE) goto ab_move_loop;

    // Reverse Futility Pruning
    if (depth < 9 && ss->static_eval - 75 * (depth - improving) >= beta) return ss->static_eval;

    // Null Move Pruning
    if (depth > 1 && ss->static_eval >= beta && st.board.hasNonPawnMaterial(st.board.sideToMove())) {
        int R = 3 + depth / 4;

        ss->move      = Move::NULL_MOVE;
        (ss + 1)->ply = ss->ply + 1;

        st.makeNullMove();
        table->prefetch_tt(st.board.hash());

        int score = -negamax(st, ss + 1, -beta, 1 - beta, depth - R, !cutnode);

        st.unmakeNullMove();

        if (score >= beta)
            // Don't return a mate score, could be a false mate
            return score >= MATE_IN_MAX ? beta : score;
    }

ab_move_loop:

    Move best_move = Move::NO_MOVE;
    int best_score = -2 * MATE;
    int score      = 0;
    int flag       = FLAG_ALPHA;

    ss->move_cnt = 0;

    Movelist moves;
    movegen::legalmoves(moves, st.board);
    score_moves(st, ss, moves, tt_move);

    for (int i = 0; i < moves.size(); i++) {
        // Incremental Move Sorting
        moves.sort(i);
        Move move = moves[i];

        if (!root) {
            // History Pruning
            if (move.score() < -4000 * depth) break;

            // Late Move Pruning
            // if (ss->move_cnt > depth * depth / (2 - improving)) break;
        } else if (i == 0) {
            st.bestmove = moves[0];
        }

        bool quiet = !(st.board.isCapture(move) || move.typeOf() == Move::PROMOTION);

        ss->move = move;
        ss->move_cnt++;
        (ss + 1)->ply = ss->ply + 1;

        st.makeMove(move);
        table->prefetch_tt(st.board.hash());

        // Late Move Reductions
        if (!in_check && depth > 2 && ss->move_cnt > 1 + 2 * pv_node) {
            int R = LMR_TABLE[depth][ss->move_cnt];

            R -= pv_node;
            R -= move.score() >= MoveGenStage::KILLER_2;

            score = -negamax(st, ss + 1, -alpha - 1, -alpha, depth - R, true);

            if (score > alpha && R > 1) {
                score = -negamax(st, ss + 1, -alpha - 1, -alpha, depth - 1, !cutnode);
            }

        } else if (!pv_node || ss->move_cnt > 1) {
            score = -negamax(st, ss + 1, -alpha - 1, -alpha, depth - 1, !cutnode);
        }

        if (pv_node && (ss->move_cnt == 1 || score > alpha)) {
            score = -negamax(st, ss + 1, -beta, -alpha, depth - 1, false);
        }

        st.unmakeMove(move);

        if (score > best_score) {
            best_score = score;
            best_move  = move;

            if (root) st.bestmove = best_move;

            if (best_score > alpha) {
                alpha = best_score;
                flag  = FLAG_EXACT;
            }
            if (alpha >= beta) {
                flag = FLAG_BETA;

                update_history(st, move, moves, depth * depth);

                if (quiet) {
                    if (move != ss->killers[0]) {
                        ss->killers[1] = ss->killers[0];
                        ss->killers[0] = move;
                    }
                }

                break;
            }
        }

        // if (root) {
        //     std::cout << ss->move_cnt << ' ' << move << ' ' << move.score() << ' ' << score << std::endl;
        // }
    }

    if (moves.size() == 0) best_score = in_check ? -MATE + ss->ply : 0;

    if (!st.info.stopped) {
        table->store(st.board.hash(), flag, best_move, depth, score_to_tt(best_score, ss->ply), ss->static_eval);
    }

    return best_score;
}

int q_search(SearchThread& st, SearchStack* ss, int alpha, int beta) {
    // Increment total nodes
    st.nodes++;

    // Check for time up every 2048 nodes
    if ((st.nodes & 2047) == 0) st.check_time();
    // Exit search if time over
    if (st.info.stopped) return 0;

    // Check for draw by repetition && draw by 50-move rule
    if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return 0;

    // Ply cap to prevent endless search
    if (ss->ply >= MAX_PLY) return evaluate(st.board);

    // Probe Transposition Table
    bool tt_hit  = false;
    TTEntry& tte = table->probe_entry(st.board.hash(), tt_hit);
    Move tt_move = Move::NO_MOVE;

    if (tt_hit) {
        tt_move      = tte.move;
        int tt_score = score_from_tt(tte.score, ss->ply);
        if ((tte.flag & (tt_score >= beta ? FLAG_BETA : FLAG_ALPHA))) return tt_score;
    }

    ss->static_eval = tt_hit ? tte.eval : evaluate(st.board);

    // Delta Pruning
    alpha = std::max(alpha, ss->static_eval);
    if (alpha >= beta) return beta;

    int best_score = ss->static_eval;
    Move best_move = Move::NO_MOVE;
    int flag       = FLAG_ALPHA;
    int score      = 0;

    Movelist moves;
    if (st.board.inCheck())
        movegen::legalmoves<MoveGenType::ALL>(moves, st.board);
    else
        movegen::legalmoves<MoveGenType::CAPTURE>(moves, st.board);
    score_moves(st, moves, tt_move);

    for (int i = 0; i < moves.size(); i++) {
        moves.sort(i);
        Move move = moves[i];

        (ss + 1)->ply = ss->ply + 1;

        st.makeMove(move);
        table->prefetch_tt(st.board.hash());

        score = -q_search(st, ss + 1, -beta, -alpha);

        st.unmakeMove(move);

        if (score > best_score) {
            best_score = score;
            best_move  = move;

            if (best_score > alpha) {
                alpha = best_score;
            }
            if (alpha >= beta) {
                flag = FLAG_BETA;
                break;
            }
        }
    }

    if (!st.info.stopped) {
        table->store(st.board.hash(), flag, best_move, 0, score_to_tt(best_score, ss->ply), ss->static_eval);
    }

    return best_score;
}