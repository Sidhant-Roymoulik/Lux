#pragma once

#include <cmath>

#include "chess.hpp"
#include "types.h"

using namespace chess;

using Time = std::chrono::milliseconds::rep;  // A value in milliseconds
static_assert(sizeof(Time) == sizeof(int64_t), "Time should be 64 bits");
inline Time now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
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

    void set_time(Color side) {
        constexpr int safety_overhead = 20;
        Time uci_time                 = (side == Color::WHITE ? wtime : btime);
        Time inc                      = (side == Color::WHITE ? winc : binc);

        if (movestogo != -1) {
            stoptime_max = uci_time / movestogo - safety_overhead;

        } else if (movetime == -1) {
            uci_time /= 30;
            uci_time -= safety_overhead;

            stoptime_max = uci_time + inc;

        } else if (movetime != -1) {
            stoptime_max = movetime - safety_overhead;
        }

        end_time = start_time + stoptime_max;
    }

    bool check_time() { return now() > end_time; }
};