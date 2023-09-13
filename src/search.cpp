#include "search.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "eval.h"
#include "move_score.h"
#include "tt.h"
#include "types.h"

static inline bool moveExists(Board& board, Move move) {
    Movelist list;
    movegen::legalmoves(list, board);

    if (list.find(move) > -1) {
        return true;
    }

    return false;
}

static void getPvLines(SearchThread& st, std::vector<U64>& positions, Move bestmove = Move::NO_MOVE) {
    if (positions.size() >= MAX_PLY) {
        return;
    }

    if (bestmove != Move::NO_MOVE) {
        std::cout << " " << uci::moveToUci(bestmove);
        positions.push_back(st.board.hash());
        st.makeMove(bestmove);
        getPvLines(st, positions);
        st.unmakeMove(bestmove);

        return;
    }

    auto pvMove = table->probe_move(st.board.hash());

    if (pvMove != Move::NO_MOVE && moveExists(st.board, pvMove)) {
        for (auto& pos : positions) {
            if (pos == st.board.hash()) {
                return;
            }
        }
        std::cout << " " << uci::moveToUci(pvMove);
        positions.push_back(st.board.hash());

        st.makeMove(pvMove);
        getPvLines(st, positions);
        st.unmakeMove(pvMove);
    }
    return;
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

    auto startime = st.start_time();
    Move bestmove = Move::NO_MOVE;

    for (int current_depth = 1; current_depth <= info.depth; current_depth++) {
        score = aspiration_window(score, current_depth, st);

        if (st.info.stopped || st.stop_early()) {
            break;
        }

        bestmove   = st.bestmove;
        info.score = score;

        if constexpr (print_info) {
            if (info.print_uci) {
                auto time_elapsed = now() - startime;

                std::cout << "info";

                std::cout << " depth " << current_depth;

                std::cout << " score ";
                if (score >= -CHECKMATE && score <= IS_MATED_IN_MAX_PLY) {
                    std::cout << "mate " << ((-CHECKMATE - score) / 2);
                } else if (score <= CHECKMATE && score >= IS_MATE_IN_MAX_PLY) {
                    std::cout << "mate " << ((CHECKMATE - score) / 2);
                } else {
                    std::cout << "cp " << score;
                }

                std::cout << " nodes " << st.nodes;
                std::cout << " nps " << static_cast<int>(1000.0f * st.nodes / (time_elapsed + 1));
                std::cout << " time " << static_cast<uint64_t>(time_elapsed);
                std::cout << " pv";

                std::vector<uint64_t> positions;
                getPvLines(st, positions, bestmove);

                std::cout << std::endl;
            } else {
                auto time_elapsed = now() - startime;

                printf("[%2d/%2d] > eval: %-4.2f nodes: %6.2fM speed: %-5.2f MNPS", current_depth, info.depth,
                       static_cast<float>(score / 100.0f), static_cast<float>(st.nodes / 1000000.0f),
                       static_cast<float>(1000.0f * st.nodes / (time_elapsed + 1)) / 1000000.0f);

                std::vector<uint64_t> positions;
                getPvLines(st, positions, bestmove);

                std::cout << std::endl;
            }
        }
    }

    if (print_info) {
        std::cout << "bestmove " << uci::moveToUci(bestmove) << std::endl;
    }
}

int aspiration_window(int prevEval, int depth, SearchThread& st) {
    SearchStack stack[MAX_PLY + 10], *ss = stack + 7;

    int alpha = -CHECKMATE;
    int beta  = CHECKMATE;

    return negamax(alpha, beta, depth, st, ss);
}

int negamax(int alpha, int beta, int depth, SearchThread& st, SearchStack* ss) {
    // Increment total nodes
    st.nodes++;

    // Check for time up every 2048 nodes
    if ((st.nodes & 2047) == 0) st.check_time();
    // Exit search if time over
    if (st.info.stopped) return 0;

    bool root      = (ss->ply == 0);
    bool pv_node   = beta - alpha > 1;
    bool in_check  = st.board.inCheck();
    int best_score = -2 * CHECKMATE;
    Move best_move = Move::NO_MOVE;
    int flag       = FLAG_ALPHA;
    int old_alpha  = alpha;
    int new_score  = 0;

    if (in_check) {
        depth++;
    }

    // If you reach 0-depth drop into q-search
    if (depth <= 0) {
        st.nodes--;
        return q_search(alpha, beta, st, ss);
    }

    if (!root) {
        // Ply cap to prevent endless search
        if (ss->ply >= MAX_PLY) return evaluate(st);

        // Check for draw by repetition
        if (st.board.isRepetition()) return 0;

        // Mate Distance Pruning
        alpha = std::max(alpha, mated_in(ss->ply));
        beta  = std::min(beta, mate_in(ss->ply + 1));
        if (alpha >= beta) {
            return alpha;
        }
    }

    //  Probe Tranpsosition Table
    bool ttHit         = false;
    TTEntry& tte       = table->probe_entry(st.board.hash(), ttHit);
    const int tt_score = ttHit ? score_from_tt(tte.get_score(), ss->ply) : 0;

    if (!pv_node && ttHit && tte.depth >= depth) {
        if ((tte.flag == FLAG_ALPHA && tt_score <= alpha) || (tte.flag == FLAG_BETA && tt_score >= beta) ||
            (tte.flag == FLAG_EXACT))
            return tt_score;
    }

    ss->static_eval = ttHit ? tte.get_eval() : evaluate(st);

    if (!pv_node && !in_check) {
        // Reverse Futility Pruning
        if (ss->static_eval - 75 * depth >= beta) {
            return ss->static_eval;
        }
    }

    Movelist moves;
    movegen::legalmoves(moves, st.board);
    score_moves(st, moves, tte.move);

    for (int i = 0; i < moves.size(); i++) {
        moves.sort(i);
        Move move = moves[i];

        st.makeMove(move);
        table->prefetch_tt(st.board.hash());

        (ss + 1)->ply = ss->ply + 1;

        if (pv_node && i == 0) {
            new_score = -negamax(-beta, -alpha, depth - 1, st, ss + 1);
        } else {
            new_score = -negamax(-alpha - 1, -alpha, depth - 1, st, ss + 1);
            if (new_score > alpha && new_score < beta) {
                new_score = -negamax(-beta, -alpha, depth - 1, st, ss + 1);
            }
        }

        st.unmakeMove(move);

        if (new_score > best_score) {
            best_score = new_score;
            best_move  = move;

            if (root) st.bestmove = best_move;

            if (best_score > alpha) {
                alpha = best_score;
                flag  = FLAG_EXACT;
            }
            if (alpha >= beta) {
                flag = FLAG_BETA;

                if (!st.board.isCapture(move)) {
                    st.history[(int)st.board.at<PieceType>(move.from())][move.to()] += depth * depth;
                }

                break;
            }
        }
    }

    if (moves.size() == 0) best_score = in_check ? mated_in(ss->ply) : 0;

    if (!st.info.stopped) {
        table->store(st.board.hash(), flag, best_move, depth, score_to_tt(best_score, ss->ply), ss->static_eval);
    }

    return best_score;
}

int q_search(int alpha, int beta, SearchThread& st, SearchStack* ss) {
    // Increment total nodes
    st.nodes++;

    // Check for time up every 2048 nodes
    if ((st.nodes & 2047) == 0) st.check_time();
    // Exit search if time over
    if (st.info.stopped) return 0;

    // Ply cap to prevent endless search
    if (ss->ply > MAX_PLY - 1) return evaluate(st);
    // Check for draw by repetition
    if (st.board.isRepetition()) return 0;

    // Delta Pruning
    int static_eval = evaluate(st);
    alpha           = std::max(alpha, static_eval);
    if (alpha >= beta) return beta;

    //  Probe Tranpsosition Table
    bool ttHit         = false;
    TTEntry& tte       = table->probe_entry(st.board.hash(), ttHit);
    const int tt_score = ttHit ? score_from_tt(tte.get_score(), ss->ply) : 0;

    //  Return TT score if we found a TT entry
    if (ttHit) {
        if ((tte.flag == FLAG_ALPHA && tt_score <= alpha) || (tte.flag == FLAG_BETA && tt_score >= beta) ||
            (tte.flag == FLAG_EXACT))
            return tt_score;
    }

    int new_score  = 0;
    int best_score = static_eval;
    Move best_move = Move::NO_MOVE;
    int flag       = FLAG_ALPHA;

    Movelist moves;
    if (st.board.inCheck())
        movegen::legalmoves<MoveGenType::ALL>(moves, st.board);
    else
        movegen::legalmoves<MoveGenType::CAPTURE>(moves, st.board);
    score_moves(st, moves, tte.move);

    for (int i = 0; i < moves.size(); i++) {
        moves.sort(i);
        Move move = moves[i];

        st.makeMove(move);
        table->prefetch_tt(st.board.hash());

        (ss + 1)->ply = ss->ply + 1;

        new_score = -q_search(-beta, -alpha, st, ss + 1);

        st.unmakeMove(move);

        if (new_score > best_score) {
            best_score = new_score;
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
        table->store(st.board.hash(), flag, best_move, 0, score_to_tt(best_score, ss->ply), static_eval);
    }

    return best_score;
}