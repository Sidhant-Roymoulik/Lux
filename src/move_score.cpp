#include "move_score.h"

#include "chess.hpp"
#include "history.h"
#include "search.h"
#include "types.h"

using namespace chess;

#define H1 20000

void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (moves[i] == tt_move) {
            moves[i].setScore(INT16_MAX);

        } else if (moves[i].typeOf() == Move::PROMOTION) {
            moves[i].setScore(H1 + mvv_lva[(int)moves[i].promotionType()][attacker] + 1);

        } else if (st.board.isCapture(moves[i])) {
            moves[i].setScore(H1 + mvv_lva[victim][attacker]);

        } else if (moves[i] == ss->killers[0]) {
            moves[i].setScore(H1 - 1000);

        } else if (moves[i] == ss->killers[1]) {
            moves[i].setScore(H1 - 2000);

        } else {
            moves[i].setScore(get_history(st, moves[i]));
        }
    }
}

void score_moves(SearchThread& st, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (moves[i] == tt_move) {
            moves[i].setScore(INT16_MAX);

        } else if (st.board.isCapture(moves[i])) {
            moves[i].setScore(H1 + mvv_lva[victim][attacker]);

        } else {
            moves[i].setScore(get_history(st, moves[i]));
        }
    }
}