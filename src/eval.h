#pragma once

#include "chess.hpp"
#include "types.h"

struct EvalInfo {
    int gamephase = 0;
    int score     = 0;
    double scale  = 0;

    Bitboard pawn[2];
};

void init_eval_tables();
int evaluate(Board& board);