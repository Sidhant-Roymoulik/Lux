#pragma once

#include "chess.hpp"
#include "search.h"
#include "types.h"

using namespace chess;

constexpr int16_t mvv_lva[6][6] = {
    {1006, 1005, 1004, 1003, 1002, 1001}, {2006, 2005, 2004, 2003, 2002, 2001}, {3006, 3005, 3004, 3003, 3002, 3001},
    {4006, 4005, 4004, 4003, 4002, 4001}, {5006, 5005, 5004, 5003, 5002, 5001}, {6006, 6005, 6004, 6003, 6002, 6001},
};

void score_moves(SearchThread& st, Movelist& moves);