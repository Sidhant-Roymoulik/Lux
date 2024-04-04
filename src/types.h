#pragma once

#include "chess.hpp"

using namespace chess;

#define VERSION "4.3"
#define AUTHOR "Sidhant Roymoulik"

enum score {
    MAX_PLY = 100,

    MATE         = 30000,
    MATE_IN_MAX  = MATE - MAX_PLY,
    MATED_IN_MAX = -MATE_IN_MAX,
};

constexpr int S(const int mg, const int eg) {
    // return (eg << 16) + mg;
    return static_cast<int>(static_cast<uint32_t>(eg) << 16) + mg;
}
static constexpr int mg_score(int score) { return static_cast<int16_t>(score); }
static constexpr int eg_score(int score) { return static_cast<int16_t>((score + 0x8000) >> 16); }