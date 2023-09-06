#include "search.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "eval.h"
#include "types.h"

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
        score = aspiration_window(score, current_depth, st, bestmove);

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
                if (score > MATE_CUTOFF) {
                    int pliesToMate = CHECKMATE - score;
                    int mateInN     = (pliesToMate / 2) + (pliesToMate % 2);
                    std::cout << "mate " << mateInN;
                } else if (score < -MATE_CUTOFF) {
                    int pliesToMate = -CHECKMATE - score;
                    int mateInN     = (pliesToMate / 2) + (pliesToMate % 2);
                    std::cout << "mate " << mateInN;
                } else {
                    std::cout << "cp " << score;
                }

                std::cout << " nodes " << st.nodes;
                std::cout << " nps " << static_cast<int>(1000.0f * st.nodes / (time_elapsed + 1));
                std::cout << " time " << static_cast<uint64_t>(time_elapsed);
                std::cout << " pv";

                // std::vector<uint64_t> positions;
                // getPvLines(st, positions, bestmove);

                std::cout << " " << uci::moveToUci(bestmove);

                std::cout << std::endl;
            } else {
                auto time_elapsed = now() - startime;

                printf("[%2d/%2d] > eval: %-4.2f nodes: %6.2fM speed: %-5.2f MNPS", current_depth, info.depth,
                       static_cast<float>(score / 100.0f), static_cast<float>(st.nodes / 1000000.0f),
                       static_cast<float>(1000.0f * st.nodes / (time_elapsed + 1)) / 1000000.0f);

                // std::vector<uint64_t> positions;
                // getPvLines(st, positions, bestmove);

                std::cout << " " << uci::moveToUci(bestmove);

                std::cout << std::endl;
            }
        }
    }

    if (print_info) {
        std::cout << "bestmove " << uci::moveToUci(bestmove) << std::endl;
    }
}

int aspiration_window(int prevEval, int depth, SearchThread& st, Move& bestmove) {
    SearchStack stack[MAX_PLY + 10], *ss = stack + 7;

    int alpha = -CHECKMATE;
    int beta  = CHECKMATE;

    return negamax(alpha, beta, depth, st, ss);
}

int negamax(int alpha, int beta, int depth, SearchThread& st, SearchStack* ss) {
    st.nodes++;

    if (depth <= 0) {
        return evaluate(st);
    }

    if ((st.nodes & 2047) == 0) {
        st.check_time();
    }

    Board& board  = st.board;
    bool is_root  = (ss->ply == 0);
    bool in_check = board.inCheck();

    if (!is_root) {
        if (ss->ply > MAX_PLY - 1) {
            return evaluate(st);
        }

        if (board.isRepetition()) {
            return 0;
        }
    }

    int bestscore  = -CHECKMATE;
    int move_count = 0;
    int oldAlpha   = alpha;
    Move bestmove  = Move::NO_MOVE;

    Movelist moves;
    movegen::legalmoves(moves, st.board);

    for (auto& move : moves) {
        st.makeMove(move);

        (ss + 1)->ply = ss->ply + 1;

        st.nodes++;
        move_count++;

        if (is_root && depth == 1 && move_count == 1) {
            st.bestmove = move;
        }

        int score = -negamax(-beta, -alpha, depth - 1, st, ss + 1);

        st.unmakeMove(move);

        if (st.info.stopped && !is_root) {
            return 0;
        }

        if (score > bestscore) {
            bestscore = score;

            if (score > alpha) {
                alpha    = score;
                bestmove = move;

                if (score >= beta) {
                    break;
                }
            }
        }

        if (st.info.stopped && is_root && st.bestmove != Move::NO_MOVE) {
            break;
        }
    }

    if (move_count == 0) bestscore = in_check ? ss->ply - CHECKMATE : 0;

    if (alpha != oldAlpha) {
        st.bestmove = bestmove;
    }

    return bestscore;
}