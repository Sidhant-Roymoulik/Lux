#pragma once

// Tunable search parameters exposed as UCI options for SPSA tuning.
// Integer params use "spin"; float params use "string".
struct SearchParams {
    // Aspiration Windows
    int asp_window    = 12;
    int asp_divisor   = 16196;
    int asp_delta_div = 5;

    // Reverse Futility Pruning
    float rfp_margin = 65.0f;
    int   rfp_depth  = 13;

    // Null Move Pruning
    float nmp_base    = 3.0f;
    float nmp_divisor = 4.0f;

    // Late Move Reductions
    float lmr_base    = 2.38f;
    float lmr_divisor = 2.00f;
    int lmr_move_min  = 2;

    // History
    int hist_prune       = 5147;
    float hist_bonus_mul = 0.83f;
};

inline SearchParams SP;
