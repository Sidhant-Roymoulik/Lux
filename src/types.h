#pragma once

#include "chess.hpp"

using namespace chess;

#define VERSION "3.4"
#define AUTHOR "Sidhant Roymoulik"

constexpr int16_t MAX_DEPTH           = 100;
constexpr int16_t MAX_PLY             = 100;
constexpr int16_t CHECKMATE           = 30000;
constexpr int16_t IS_MATE_IN_MAX_PLY  = CHECKMATE - MAX_PLY;
constexpr int16_t IS_MATED_IN_MAX_PLY = -IS_MATE_IN_MAX_PLY;

constexpr int mate_in(int16_t ply) { return CHECKMATE - ply; }
constexpr int mated_in(int16_t ply) { return -CHECKMATE + ply; }

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