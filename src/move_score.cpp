#pragma once

#include "move_score.h"

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

#define MOVE_SCORE_FACTOR 1000000 / INT16_MAX

void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (moves[i] == tt_move) {
            moves[i].setScore(INT16_MAX);

        } else if (moves[i].typeOf() == Move::PROMOTION) {
            moves[i].setScore(INT16_MAX - 100 + mvv_lva[(int)moves[i].promotionType()][attacker] + 1);

        } else if (st.board.isCapture(moves[i])) {
            moves[i].setScore(INT16_MAX - 100 + mvv_lva[victim][attacker]);

            // } else if (moves[i] == ss->killers[0]) {
            //     moves[i].setScore(INT16_MAX - 100);

            // } else if (moves[i] == ss->killers[1]) {
            //     moves[i].setScore(INT16_MAX - 200);

        } else {
            moves[i].setScore(st.history[attacker][moves[i].to()] / (MOVE_SCORE_FACTOR));
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
            moves[i].setScore(INT16_MAX - 100 + mvv_lva[victim][attacker]);

        } else {
            moves[i].setScore(st.history[attacker][moves[i].to()] / (MOVE_SCORE_FACTOR));
        }
    }
}