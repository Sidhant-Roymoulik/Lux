#pragma once

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

constexpr int16_t mvv_lva[6][6] = {
    {16, 15, 14, 13, 12, 11}, {26, 25, 24, 23, 22, 21}, {36, 35, 34, 33, 32, 31},
    {46, 45, 44, 43, 42, 41}, {56, 55, 54, 53, 52, 51}, {66, 65, 64, 63, 62, 61},
};

void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move);
void score_moves(SearchThread& st, Movelist& moves, Move tt_move);