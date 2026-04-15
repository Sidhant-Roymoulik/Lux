#pragma once

// Tunable search parameters exposed as UCI options for SPSA tuning.
// Integer params use "spin"; float params use "string".
struct SearchParams {
    // Aspiration Windows
    int asp_window    = 12;
    int asp_divisor   = 15963;
    int asp_delta_div = 6;

    // Reverse Futility Pruning
    float rfp_margin = 59.75f;
    int rfp_depth    = 13;

    // Null Move Pruning
    float nmp_base    = 2.35f;
    float nmp_divisor = 2.77f;

    // Late Move Reductions
    float lmr_base    = 2.15f;
    float lmr_divisor = 1.81f;
    int lmr_move_min  = 2;

    // History
    int hist_prune       = 5161;
    float hist_bonus_mul = 0.66f;

    // Time Management
    float tm_soft_multiplier = 0.65f;
    float tm_hard_multiplier = 2.44f;
    float tm_pv_floor        = 0.54f;
    float tm_pv_base         = 1.82f;
    float tm_pv_decay        = 0.10f;
};

inline SearchParams SP;
