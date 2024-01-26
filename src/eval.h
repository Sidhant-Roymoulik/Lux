#pragma once

#include "chess.hpp"
#include "types.h"

struct EvalInfo {
    int gamephase = 0;
    Score score;

    Bitboard pawn[2];
};

void init_eval_tables();
int evaluate(Board& board);