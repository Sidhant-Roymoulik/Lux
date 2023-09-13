#pragma once

#include "move_score.h"

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

#define MOVE_SCORE_FACTOR 1000000 / INT16_MAX

void score_moves(SearchThread& st, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == tt_move) {
            moves[i].setScore(INT16_MAX);
            continue;
        }

        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (st.board.isCapture(moves[i])) {
            moves[i].setScore(INT16_MAX - 100 + mvv_lva[victim][attacker]);
        } else {
            moves[i].setScore(st.history[attacker][moves[i].to()] / (MOVE_SCORE_FACTOR));
        }
    }
}