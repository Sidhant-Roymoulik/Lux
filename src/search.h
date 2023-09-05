#include <memory>

#include "time_manager.h"
#include "types.h"

using namespace chess;

struct Search_Info {
    Score score         = 0;
    Ply depth           = 0;
    uint64_t node_limit = 0;

    bool stopped   = false;
    bool print_uci = false;
    bool time_set  = false;
    bool nodes_set = false;
};

struct Search_Stack {
    Ply ply{};
    Score static_eval{};
};

struct Search_Thread {
    Board board;
    Time_Manager tm;
    Search_Info& info;

    uint64_t nodes = 0;

    Move bestmove = Move::NO_MOVE;

    Search_Thread(Search_Info& i) : info(i), board(STARTPOS) { clear(); }

    inline void clear() { nodes = 0; }
    inline void initialize() {
        tm.start_time = now();
        if (info.time_set) {
            tm.set_time(board.sideToMove());
        }
    }

    inline Time start_time() { return tm.start_time; }

    inline void makeMove(Move& move) { board.makeMove(move); }
    inline void makeMove(std::string move_uci) {
        board.makeMove(uci::uciToMove(board, move_uci));
    }
    inline void unmakeMove(Move& move) { board.unmakeMove(move); }

    inline void applyFen(std::string fen) { board.setFen(fen); }

    void check_time() {
        if ((info.time_set && tm.check_time()) ||
            (info.nodes_set && nodes >= info.node_limit)) {
            info.stopped = true;
        }
    }
};

// template <bool print_info>
// void iterative_deepening(Search_Thread& st);

// int negamax(int alpha, int beta, int depth, Search_Thread& st,
//             Search_Stack* ss);