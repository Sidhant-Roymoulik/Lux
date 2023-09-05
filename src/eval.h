#pragma once

#include "chess.hpp"
#include "eval_constants.h"
#include "search.h"
#include "types.h"

using namespace chess;

int score[2] = {0, 0};

Score evaluate(Search_Thread& st) {
    score[0] = 0;
    score[1] = 0;

    int turn = (int)st.board.sideToMove();

    for (int color = 0; color < 2; color++) {
        for (int piece_type = 0; piece_type < 6; piece_type++) {
            Bitboard copy =
                st.board.pieces(PieceType(piece_type), Color(color));

            while (copy) {
                copy &= copy - 1;

                score[color] += PIECE_VALUES[piece_type];
            }
        }
    }

    return score[turn] - score[turn ^ 1];
}