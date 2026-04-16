#pragma once

#include <chrono>
#include <cmath>

#include "search_params.h"
#include "types.h"

using namespace chess;

using Time = std::chrono::milliseconds::rep;  // A value in milliseconds
static_assert(sizeof(Time) == sizeof(int64_t), "Time should be 64 bits");
inline Time now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

struct TimeManager {
    static constexpr int safety_overhead = 50;

    // UCI inputs
    Time wtime         = 0;
    Time btime         = 0;
    Time winc          = 0;
    Time binc          = 0;
    Time movetime      = 0;
    int64_t movestogo  = 0;
    int64_t node_limit = 0;

    // Computed state
    Time start_time         = 0;
    Time soft_time_limit    = 0;
    Time hard_time_limit    = 0;
    Move last_best_move     = Move::NO_MOVE;
    int best_move_stability = 0;

    void reset() {
        wtime      = 0;
        btime      = 0;
        winc       = 0;
        binc       = 0;
        movetime   = 0;
        movestogo  = 0;
        node_limit = 0;

        soft_time_limit = 0;
        hard_time_limit = 0;

        last_best_move      = Move::NO_MOVE;
        best_move_stability = 0;
    }

    bool time_is_set() const { return wtime != 0 || btime != 0 || movetime != 0; }

    Time elapsed() { return now() - start_time; }

    void set_time(Color side) {
        best_move_stability = 0;
        start_time          = now();

        Time remaining_time = (side == Color::WHITE ? wtime : btime);
        Time increment      = (side == Color::WHITE ? winc : binc);

        if (movetime > 0) {
            soft_time_limit = movetime;
            hard_time_limit = movetime;
            return;
        }

        int64_t moves   = movestogo > 0 ? movestogo : 30;
        Time base       = (remaining_time + (increment * moves) - safety_overhead) / moves;
        soft_time_limit = SP.tm_soft_multiplier * base;
        hard_time_limit = SP.tm_hard_multiplier * base;

        soft_time_limit = std::min(soft_time_limit, remaining_time - safety_overhead);
        hard_time_limit = std::min(hard_time_limit, remaining_time - safety_overhead);
    }

    void update_stability(Move best_move) {
        if (best_move == last_best_move) {
            best_move_stability++;
        } else {
            best_move_stability = 0;
            last_best_move      = best_move;
        }
    }

    bool soft_limit_reached() {
        if (!time_is_set()) return false;

        float pv_factor = std::max(SP.tm_pv_floor, SP.tm_pv_base - SP.tm_pv_decay * best_move_stability);
        return elapsed() > static_cast<Time>(soft_time_limit * pv_factor);
    }

    // Called every 2048 nodes.
    bool hard_limit_reached(uint64_t nodes) {
        return (time_is_set() && elapsed() > hard_time_limit) ||
               (node_limit > 0 && nodes >= static_cast<uint64_t>(node_limit));
    }
};