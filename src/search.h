#pragma once

#include <memory>

#include "chess.hpp"
#include "time_manager.h"
#include "tt.h"
#include "types.h"

using namespace chess;

// Global Transposition Table
extern TranspositionTable* table;

struct SearchInfo {
    int score           = 0;
    Ply depth           = 0;
    uint64_t node_limit = 0;

    bool stopped   = false;
    bool print_uci = false;
    bool time_set  = false;
    bool nodes_set = false;
};

struct SearchStack {
    Ply ply{};
    int static_eval{};
    // Move killers[2]{};
};

struct SearchThread {
    Board board;
    Time_Manager tm;
    SearchInfo& info;

    uint64_t nodes = 0;
    int history[6][64];

    Move bestmove = Move::NO_MOVE;

    SearchThread(SearchInfo& i) : info(i), board(STARTPOS) { clear(); }

    inline void clear() {
        nodes = 0;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 64; j++) {
                history[i][j] = 0;
            }
        }
    }
    inline void initialize() {
        tm.start_time = now();
        if (info.time_set) {
            tm.set_time(board.sideToMove());
        }
    }

    inline Time start_time() { return tm.start_time; }

    inline void makeMove(Move& move) { board.makeMove(move); }
    inline void makeMove(std::string move_uci) { board.makeMove(uci::uciToMove(board, move_uci)); }
    inline void unmakeMove(Move& move) { board.unmakeMove(move); }

    inline void applyFen(std::string fen) { board.setFen(fen); }

    inline bool stop_early() { return info.time_set && (tm.check_time() || info.stopped); }
    void check_time() {
        if ((info.time_set && tm.check_time()) || (info.nodes_set && nodes >= info.node_limit)) {
            info.stopped = true;
        }
    }
};

template <bool print_info>
void iterative_deepening(SearchThread& st);

int aspiration_window(int prevEval, int depth, SearchThread& st);
int negamax(int alpha, int beta, int depth, SearchThread& st, SearchStack* ss);
int q_search(int alpha, int beta, SearchThread& st, SearchStack* ss);