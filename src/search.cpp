#include "search.h"

#include "eval.h"
#include "move_score.h"
#include "pv.h"

// Late-Move Precomputations
int LMR_TABLE[MAX_PLY][constants::MAX_MOVES];

void init_search_tables() {
    for (int depth = 1; depth < MAX_PLY; depth++) {
        for (int move = 1; move < chess::constants::MAX_MOVES; move++) {
            LMR_TABLE[depth][move] = SP.lmr_base + log(depth) * log(move) / SP.lmr_divisor;
        }
    }
}

// Explicit template instantiation
template void iterative_deepening<false>(SearchThread& st);
template void iterative_deepening<true>(SearchThread& st);

template <bool print_info>
void iterative_deepening(SearchThread& st) {
    st.clear();
    st.initialize();

    int score = 0;

    auto start_time = st.start_time();
    Move bestmove   = Move::NO_MOVE;

    for (int current_depth = 1; current_depth <= st.depth; current_depth++) {
        score = aspiration_window(score, current_depth, st);

        if (st.stopped || st.stop_early()) break;

        bestmove = st.bestmove;
        st.score = score;

        if constexpr (print_info) {
            if (st.print_uci) {
                auto time_elapsed = now() - start_time;

                std::cout << "info";

                std::cout << " depth " << current_depth;

                std::cout << " score ";
                if (score >= -MATE && score <= MATED_IN_MAX) {
                    std::cout << "mate " << ((-MATE - score - 1) / 2);
                } else if (score <= MATE && score >= MATE_IN_MAX) {
                    std::cout << "mate " << ((MATE - score + 1) / 2);
                } else {
                    std::cout << "cp " << score;
                }

                std::cout << " nodes " << st.nodes;
                std::cout << " nps " << static_cast<int>(1000.0f * st.nodes / (time_elapsed + 1));
                std::cout << " time " << static_cast<uint64_t>(time_elapsed);
                std::cout << " pv";

                get_pv(st, bestmove);

                std::cout << std::endl;
            } else {
                auto time_elapsed = now() - start_time;

                printf("[%2d/%2d] > eval: %-4.2f nodes: %6.2fM speed: %-5.2f MNPS", current_depth, st.depth,
                       static_cast<float>(score / 100.0f), static_cast<float>(st.nodes / 1000000.0f),
                       static_cast<float>(1000.0f * st.nodes / (time_elapsed + 1)) / 1000000.0f);

                get_pv(st, bestmove);

                std::cout << std::endl;
            }
        }
    }

    if (print_info) {
        // Fall back to st.bestmove if no depth completed cleanly (e.g. stopped mid-depth-1)
        if (bestmove == Move::NO_MOVE) bestmove = st.bestmove;
        std::cout << "bestmove " << uci::moveToUci(bestmove) << std::endl;
    }
}

int aspiration_window(int prev, int depth, SearchThread& st) {
    // ss starts 7 slots into the stack so (ss-2) and (ss-1) are valid without bounds checks
    SearchStack stack[MAX_PLY + 10], *ss = stack + 7;

    int delta = SP.asp_window + prev * prev / SP.asp_divisor;
    int alpha = std::max(prev - delta, -MATE);
    int beta  = std::min(prev + delta, static_cast<int>(MATE));

    int score = 0;
    while (true) {
        score = negamax(st, ss, alpha, beta, depth, false);

        if (st.stopped) break;

        if (score <= alpha) {
            beta  = (alpha + beta) / 2;
            alpha = std::max(score - delta, -MATE);

        } else if (score >= beta) {
            beta = std::min(score + delta, static_cast<int>(MATE));

        } else
            break;

        delta += delta / SP.asp_delta_div;
    }

    return score;
}

int negamax(SearchThread& st, SearchStack* ss, int alpha, int beta, int depth, bool cutnode) {
    if (st.count_node()) return 0;

    bool root    = (ss->ply == 0);
    bool pv_node = beta - alpha > 1;

    if (!root) {
        if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return 0;
        if (ss->ply >= MAX_PLY) return evaluate(st.board);

        // Mate Distance Pruning
        alpha = std::max(alpha, -MATE + ss->ply);
        beta  = std::min(beta, MATE - ss->ply - 1);
        if (alpha >= beta) return alpha;
    }

    bool in_check = st.board.inCheck();

    if (in_check) depth++;

    if (depth <= 0) {
        st.nodes--;
        return q_search(st, ss, alpha, beta);
    }

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

    // Skip static-eval pruning for PV nodes, in-check, and post-null-move positions.
    // goto keeps the pruning blocks flat rather than nesting in a large if/else chain.
    if (pv_node || in_check || (ss - 1)->move == Move::NULL_MOVE) goto ab_move_loop;

    // Reverse Futility Pruning
    if (depth < SP.rfp_depth && ss->static_eval - SP.rfp_margin * (depth - improving) >= beta) return ss->static_eval;

    // Null Move Pruning — guarded by non-pawn material to avoid zugzwang
    if (depth > 1 && ss->static_eval >= beta && st.board.hasNonPawnMaterial(st.board.sideToMove())) {
        int R = static_cast<int>(SP.nmp_base + depth / SP.nmp_divisor);

        ss->move      = Move::NULL_MOVE;
        (ss + 1)->ply = ss->ply + 1;

        st.make_null_move();
        table->prefetch_tt(st.board.hash());

        int score = -negamax(st, ss + 1, -beta, 1 - beta, depth - R, !cutnode);

        st.unmake_null_move();

        if (score >= beta)
            return score >= MATE_IN_MAX ? beta : score;  // don't return a false mate
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

    for (int move_idx = 0; move_idx < moves.size(); move_idx++) {
        sort_moves(moves, move_idx);
        Move move = moves[move_idx];

        if (!root) {
            if (move.score() < -SP.hist_prune * depth) break;
        } else if (move_idx == 0) {
            st.bestmove = moves[0];
        }

        bool quiet = !(st.board.isCapture(move) || move.typeOf() == Move::PROMOTION);

        ss->move = move;
        ss->move_cnt++;
        (ss + 1)->ply = ss->ply + 1;

        st.make_move(move);
        table->prefetch_tt(st.board.hash());

        // Late Move Reductions — re-search at depth-1 if reduced score beats alpha
        if (!in_check && depth > 2 && ss->move_cnt > SP.lmr_move_min + 2 * pv_node) {
            int R = LMR_TABLE[std::min(depth, MAX_PLY - 1)][std::min(ss->move_cnt, chess::constants::MAX_MOVES - 1)];

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

        st.unmake_move(move);

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

                update_history(st, move, moves, static_cast<int>(std::round(depth * depth * SP.hist_bonus_mul)));

                if (quiet) {
                    if (move != ss->killers[0]) {
                        ss->killers[1] = ss->killers[0];
                        ss->killers[0] = move;
                    }
                }

                break;
            }
        }
    }

    if (moves.size() == 0) best_score = in_check ? -MATE + ss->ply : 0;

    if (!st.stopped) {
        table->store(st.board.hash(), flag, best_move, depth, score_to_tt(best_score, ss->ply), ss->static_eval);
    }

    return best_score;
}

int q_search(SearchThread& st, SearchStack* ss, int alpha, int beta) {
    if (st.count_node()) return 0;

    if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return 0;
    if (ss->ply >= MAX_PLY) return evaluate(st.board);

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
        movegen::legalmoves<movegen::MoveGenType::ALL>(moves, st.board);
    else
        movegen::legalmoves<movegen::MoveGenType::CAPTURE>(moves, st.board);
    score_moves<true>(st, nullptr, moves, tt_move);

    for (int move_idx = 0; move_idx < moves.size(); move_idx++) {
        sort_moves(moves, move_idx);
        Move move = moves[move_idx];

        (ss + 1)->ply = ss->ply + 1;

        st.make_move(move);
        table->prefetch_tt(st.board.hash());

        score = -q_search(st, ss + 1, -beta, -alpha);

        st.unmake_move(move);

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

    if (!st.stopped) {
        table->store(st.board.hash(), flag, best_move, 0, score_to_tt(best_score, ss->ply), ss->static_eval);
    }

    return best_score;
}
