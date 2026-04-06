#pragma once

// Tunable search parameters exposed as UCI spin options for SPSA tuning.
// Float-valued params are scaled x100 (e.g. LmrBase 200 == 2.0).
struct SearchParams {
    // Aspiration Windows
    int asp_window    = 12;
    int asp_divisor   = 16196;
    int asp_delta_div = 5;

    // Reverse Futility Pruning
    int rfp_margin = 65;
    int rfp_depth  = 13;

    // Null Move Pruning
    int nmp_base    = 3;
    int nmp_divisor = 4;

    // Late Move Reductions (scaled x100)
    int lmr_base     = 238;  // 2.38 * 100
    int lmr_divisor  = 200;  // 2.00 * 100
    int lmr_move_min = 2;

    // History
    int hist_prune     = 5147;
    int hist_bonus_mul = 83;  // scaled x100
};

inline SearchParams SP;
