#pragma once

#include "search_params.h"
#include "time_manager.h"
#include "tt.h"

using namespace chess;

// Global Transposition Table
extern TranspositionTable* table;

struct SearchStack {
    int16_t ply{};
    Move killers[2]{};
    Move move{};
    int static_eval{};
    int move_cnt{};
};

struct SearchThread {
    Board board;
    TimeManager tm;
    int history[13][64];  // [piece (0-12, chess.hpp Piece enum)][to_square]

    uint64_t nodes = 0;
    Move bestmove  = Move::NO_MOVE;

    int score           = 0;
    int16_t depth       = 0;
    uint64_t node_limit = 0;

    bool stopped   = false;
    bool print_uci = false;
    bool time_set  = false;
    bool nodes_set = false;

    SearchThread() {
        board = Board(constants::STARTPOS);
        clear();
    }

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
        if (time_set) {
            tm.set_time(board.sideToMove());
        }
    }

    Time start_time() { return tm.start_time; }

    void make_move(Move& move) { board.makeMove(move); }
    void make_move(std::string move_uci) { board.makeMove(uci::uciToMove(board, move_uci)); }
    void unmake_move(Move& move) { board.unmakeMove(move); }

    void make_null_move() { board.makeNullMove(); }
    void unmake_null_move() { board.unmakeNullMove(); }

    void set_fen(std::string fen) { board.setFen(fen); }

    bool stop_early() { return stopped || (time_set && tm.check_time()); }
    void check_time() {
        if ((time_set && tm.check_time()) || (nodes_set && nodes >= node_limit)) stopped = true;
    }

    // Increments the node counter and checks time every 2048 nodes.
    // Returns true if the search should terminate immediately.
    [[nodiscard]] inline bool count_node() {
        nodes++;
        if ((nodes & 2047) == 0) check_time();
        return stopped;
    }
};

void init_search_tables();

template <bool print_info>
void iterative_deepening(SearchThread& st);

int aspiration_window(int prev_score, int depth, SearchThread& st);
int negamax(SearchThread& st, SearchStack* ss, int alpha, int beta, int depth, bool cutnode);
int q_search(SearchThread& st, SearchStack* ss, int alpha, int beta);