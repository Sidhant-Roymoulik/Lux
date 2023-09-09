#pragma once

#include "move_score.h"

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

void score_moves(SearchThread& st, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == tt_move) {
            moves[i].setScore(30000);
            continue;
        }

        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (st.board.isCapture(moves[i])) {
            moves[i].setScore(mvv_lva[victim][attacker]);
        }
    }
}