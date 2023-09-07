#pragma once

#include "move_score.h"

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

void score_moves(SearchThread& st, Movelist& moves) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (st.board.isCapture(moves[i])) {
            moves[i].setScore(mvv_lva[victim][attacker]);
        }
    }
}