#include "search.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "eval.h"
#include "move_score.h"
#include "tt.h"
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
    // If you reach 0-depth drop into q-search
    if (depth <= 0) {
        st.nodes--;
        return q_search(alpha, beta, st, ss);
    }

    bool root = (ss->ply == 0);

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

    if (!root && ttHit && tte.depth >= depth) {
        if ((tte.flag == FLAG_ALPHA && tt_score <= alpha) || (tte.flag == FLAG_BETA && tt_score >= beta) ||
            (tte.flag == FLAG_EXACT))
            return tt_score;
    }

    ss->static_eval = ttHit ? tte.get_eval() : evaluate(st);

    bool in_check  = st.board.inCheck();
    int best_score = -2 * CHECKMATE;
    Move best_move = Move::NO_MOVE;
    int old_alpha  = alpha;
    int new_score  = 0;

    Movelist moves;
    movegen::legalmoves(moves, st.board);
    score_moves(st, moves, tte.move);

    for (int i = 0; i < moves.size(); i++) {
        moves.sort(i);
        Move move = moves[i];

        st.makeMove(move);

        (ss + 1)->ply = ss->ply + 1;

        new_score = -negamax(-beta, -alpha, depth - 1, st, ss + 1);

        st.unmakeMove(move);

        if (new_score > best_score) {
            best_score = new_score;
            best_move  = move;

            if (root) st.bestmove = best_move;

            alpha = std::max(alpha, best_score);
            if (alpha >= beta) {
                break;
            }
        }
    }

    if (moves.size() == 0) best_score = in_check ? mated_in(ss->ply) : 0;

    int flag = best_score >= beta ? FLAG_BETA : (alpha != old_alpha) ? FLAG_EXACT : FLAG_ALPHA;

    table->store(st.board.hash(), flag, best_move, depth, score_to_tt(best_score, ss->ply), ss->static_eval);

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

    Movelist moves;
    movegen::legalmoves<MoveGenType::CAPTURE>(moves, st.board);
    score_moves(st, moves, tte.move);

    for (int i = 0; i < moves.size(); i++) {
        moves.sort(i);
        Move move = moves[i];

        st.makeMove(move);

        (ss + 1)->ply = ss->ply + 1;

        new_score = -q_search(-beta, -alpha, st, ss + 1);

        st.unmakeMove(move);

        if (new_score > best_score) {
            best_score = new_score;
            best_move  = move;

            alpha = std::max(alpha, best_score);
            if (alpha >= beta) {
                break;
            }
        }
    }

    int flag = best_score >= beta ? FLAG_BETA : FLAG_ALPHA;

    table->store(st.board.hash(), flag, best_move, 0, score_to_tt(best_score, ss->ply), static_eval);

    return best_score;
}