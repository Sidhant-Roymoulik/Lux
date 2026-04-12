#pragma once

// Tunable search parameters exposed as UCI options for SPSA tuning.
// Integer params use "spin"; float params use "string".
struct SearchParams {
    // Aspiration Windows
    int asp_window    = 12;
    int asp_divisor   = 16777;
    int asp_delta_div = 5;

    // Reverse Futility Pruning
    float rfp_margin = 64.97f;
    int rfp_depth    = 14;

    // Null Move Pruning
    float nmp_base    = 2.29f;
    float nmp_divisor = 2.74f;

    // Late Move Reductions
    float lmr_base    = 2.37f;
    float lmr_divisor = 1.92f;
    int lmr_move_min  = 2;

    // History
    int hist_prune       = 5201;
    float hist_bonus_mul = 0.73f;

    // Time Management
    float tm_soft_multiplier = 0.60f;
    float tm_hard_multiplier = 2.00f;
    float tm_pv_floor        = 0.50f;
    float tm_pv_base         = 2.00f;
    float tm_pv_decay        = 0.10f;
};

inline SearchParams SP;
