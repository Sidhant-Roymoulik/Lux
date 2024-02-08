#pragma once

#include "search.h"
#include "types.h"

using namespace chess;

enum MoveGenStage {
    TT_MOVE  = INT16_MAX,
    CAPTURE  = 20000,
    KILLER_1 = 19000,
    KILLER_2 = 18000,
};

constexpr int16_t mvv_lva[6] = {10, 32, 33, 50, 90, 0};

void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move);
void score_moves(SearchThread& st, Movelist& moves, Move tt_move);