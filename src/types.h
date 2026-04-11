#pragma once

#include "chess.hpp"

using namespace chess;

inline constexpr const char* VERSION = "5.0";
inline constexpr const char* AUTHOR  = "Sidhant Roymoulik";

inline constexpr int DEFAULT_HASH_SIZE = 64;
inline constexpr int MIN_HASH_SIZE     = 4;
inline constexpr int MAX_HASH_SIZE     = 8192;

inline constexpr int MAX_THREADS = 64;

enum score {
    MAX_PLY = 100,

    MATE         = 30000,
    MATE_IN_MAX  = MATE - MAX_PLY,
    MATED_IN_MAX = -MATE_IN_MAX,
};

// Scores are packed: the endgame value occupies the upper 16 bits and the
// midgame value occupies the lower 16 bits, both stored as signed int16_t.
// S(mg, eg) packs them; mg_score() / eg_score() unpack them.
// The +0x8000 in eg_score handles two's-complement sign extension correctly.
constexpr int S(const int mg, const int eg) { return static_cast<int>(static_cast<uint32_t>(eg) << 16) + mg; }

static constexpr int mg_score(int score) { return static_cast<int16_t>(score); }
static constexpr int eg_score(int score) { return static_cast<int16_t>((score + 0x8000) >> 16); }