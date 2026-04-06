#pragma once

// Tunable search parameters exposed as UCI spin options for SPSA tuning.
// Float-valued params are scaled x100 (e.g. LmrBase 200 == 2.0).
struct SearchParams {
    // Aspiration Windows
    int asp_window  = 10;
    int asp_divisor = 16000;

    // Reverse Futility Pruning
    int rfp_margin = 75;

    // Null Move Pruning
    int nmp_base    = 3;
    int nmp_divisor = 4;

    // Late Move Reductions (scaled x100)
    int lmr_base    = 200;  // 2.0 * 100
    int lmr_divisor = 250;  // 2.5 * 100

    // History Pruning
    int hist_prune = 4000;
};

inline SearchParams SP;
