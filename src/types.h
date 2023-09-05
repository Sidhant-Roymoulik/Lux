#pragma once

#include "chess.hpp"

using namespace chess;

#define NAME "Lux"
#define AUTHOR "Sidhant Roymoulik"

using Ply  = int16_t;
using Hash = uint64_t;

constexpr Ply MAX_DEPTH   = 100;
constexpr Ply MAX_PLY     = 100;
constexpr int CHECKMATE   = 100000;
constexpr int MATE_CUTOFF = 50000;

struct Score {
    int mg = 0;
    int eg = 0;
    Score(int a, int b) {
        mg = a;
        eg = b;
    }
    Score() {
        mg = 0;
        eg = 0;
    }
    Score operator+(const Score x) { return Score(mg + x.mg, eg + x.eg); }
    Score operator-(const Score x) { return Score(mg - x.mg, eg - x.eg); }
    Score operator*(int x) { return Score(mg * x, eg * x); }
    void operator+=(const Score x) {
        mg += x.mg;
        eg += x.eg;
    }
    void operator-=(const Score x) {
        mg -= x.mg;
        eg -= x.eg;
    }
};