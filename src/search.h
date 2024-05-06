#pragma once

#include "time_manager.h"
#include "tt.h"

using namespace chess;

// Global Transposition Table
extern TranspositionTable* table;

struct SearchInfo {
    int score           = 0;
    int16_t depth       = 0;
    uint64_t node_limit = 0;

    bool stopped   = false;
    bool print_uci = false;
    bool time_set  = false;
    bool nodes_set = false;
};

struct SearchStack {
    int16_t ply{};
    Move killers[2]{};
    Move move{};
    int static_eval{};
    int move_cnt{};
};

struct SearchThread {
    Board board;
    SearchInfo& info;
    Time_Manager tm;

    SearchThread(SearchInfo& i) : info(i) {
        board = Board(constants::STARTPOS);
        clear();
    }

    uint64_t nodes = 0;
    Move bestmove  = Move::NO_MOVE;
    int history[13][64];

    void clear() {
        nodes    = 0;
        bestmove = Move::NO_MOVE;
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 64; j++) {
                history[i][j] = 0;
            }
        }
    }
    void initialize() {
        tm.start_time = now();
        if (info.time_set) {
            tm.set_time(board.sideToMove());
        }
    }

    Time start_time() { return tm.start_time; }

    void makeMove(Move& move) { board.makeMove(move); }
    void makeMove(std::string move_uci) { board.makeMove(uci::uciToMove(board, move_uci)); }
    void unmakeMove(Move& move) { board.unmakeMove(move); }

    void makeNullMove() { board.makeNullMove(); }
    void unmakeNullMove() { board.unmakeNullMove(); }

    void applyFen(std::string fen) { board.setFen(fen); }

    bool stop_early() { return info.stopped || (info.time_set && tm.check_time_opt()); }
    void check_time() {
        if ((info.time_set && tm.check_time_max()) || (info.nodes_set && nodes >= info.node_limit)) info.stopped = true;
    }
};

void init_search_tables();

template <bool print_info>
void iterative_deepening(SearchThread& st);

int aspiration_window(int prevEval, int depth, SearchThread& st);
int negamax(SearchThread& st, SearchStack* ss, int alpha, int beta, int depth, bool cutnode);
int q_search(SearchThread& st, SearchStack* ss, int alpha, int beta);