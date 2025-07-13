#pragma once

#include <chrono>
#include <cmath>

#include "types.h"

using namespace chess;

using Time = std::chrono::milliseconds::rep;  // A value in milliseconds
static_assert(sizeof(Time) == sizeof(int64_t), "Time should be 64 bits");
inline Time now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

// Stability scale from Stash
const double stability_scale[5] = {2.50, 1.20, 0.90, 0.80, 0.75};

struct Time_Manager {
    Time wtime = -1;
    Time btime = -1;
    Time winc  = 0;
    Time binc  = 0;

    int movestogo = -1;
    Time movetime = -1;

    Time start_time{};

    Time avg_time{};
    Time max_time{};
    Time opt_time{};

    Move prev_bestmove{Move::NO_MOVE};
    int stability{};

    void set_time(Color side) {
        Time overhead = 20;

        if (movetime != -1) {
            avg_time = max_time = opt_time = movetime - overhead;
        }

        else {
            Time time  = (side == Color::WHITE) ? wtime : btime;
            Time inc   = (side == Color::WHITE) ? winc : binc;
            double mtg = (movestogo != -1) ? movestogo : 40.0;

            time = time - overhead;

            avg_time = time / mtg + inc;
            max_time = time / std::pow(mtg, 0.4) + inc;

            avg_time = std::min(time, avg_time);
            max_time = std::min(time, max_time);
            opt_time = max_time;
        }

        prev_bestmove = Move::NO_MOVE;
        stability     = 0;
    }

    void update_tm(Move bestmove) {
        if (prev_bestmove != bestmove) {
            prev_bestmove = bestmove;
            stability     = 0;
        } else
            stability = std::min(stability + 1, 4);

        double scale = stability_scale[stability];

        opt_time = std::min<Time>(max_time, avg_time * scale);
    }

    bool check_time_opt() { return now() > start_time + opt_time; }
    bool check_time_max() { return now() > start_time + max_time; }
};