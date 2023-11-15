#pragma once

#include "search.h"

struct EvalInfo {
    int gamephase = 0;
    Score score;

    Bitboard pawn[2];
};

void init_eval_tables();
int evaluate(Board& board);