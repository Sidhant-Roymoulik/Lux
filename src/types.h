#pragma once

#include "chess.hpp"

using namespace chess;

#define VERSION "4.1"
#define AUTHOR "Sidhant Roymoulik"

enum score {
    MAX_PLY = 100,

    MATE         = 30000,
    MATE_IN_MAX  = MATE - MAX_PLY,
    MATED_IN_MAX = -MATE_IN_MAX,
};

struct Score {
    int mg = 0, eg = 0;

    Score() : mg(0), eg(0) {}
    Score(int a, int b) : mg(a), eg(b) {}

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