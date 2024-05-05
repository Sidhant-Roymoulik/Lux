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

struct Time_Manager {
    Time wtime = -1;
    Time btime = -1;
    Time winc  = 0;
    Time binc  = 0;

    int movestogo = -1;
    Time movetime = -1;

    Time start_time{};
    Time end_time{};

    Time stoptime_max{};
    Time stoptime_opt{};

    void set_time(Color side) {
        Time overhead = 20;
        Time uci_time = (side == Color::WHITE ? wtime : btime);
        Time inc      = (side == Color::WHITE ? winc : binc);

        if (movestogo != -1) {
            stoptime_opt = stoptime_max = std::max(overhead, uci_time / movestogo - overhead);

        } else if (movetime == -1) {
            uci_time /= 30;
            uci_time -= overhead;

            Time time = uci_time + inc;

            stoptime_opt = time / 2;
            stoptime_max = std::min(uci_time, time);

        } else if (movetime != -1)
            stoptime_opt = stoptime_max = movetime - overhead;
    }

    bool check_time_opt() { return now() > start_time + stoptime_opt; }
    bool check_time_max() { return now() > start_time + stoptime_max; }
};