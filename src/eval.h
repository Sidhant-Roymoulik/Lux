#pragma once

#include "eval_constants.h"

struct EvalInfo {
    int gamephase = 0;
    int score     = 0;
    double scale  = 0;

    Bitboard pawn[2];
    Bitboard pawn_attacks[2];
};

void init_eval_tables();
int evaluate(const Board& board);