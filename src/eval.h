#pragma once

#include "types.h"

struct EvalInfo {
    int gamephase = 0;
    int score     = 0;
    double scale  = 0;

    Bitboard pawn[2];
};

void init_eval_tables();
int evaluate(const Board& board);