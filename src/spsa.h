#pragma once

#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include "search_params.h"

// Forward declaration — avoids including search.h
void init_search_tables();

static constexpr float SP_LO = 0.5f;
static constexpr float SP_HI = 2.0f;

struct TunableParam {
    const char* name;
    enum Type { INT, FLOAT } type;
    void* ptr;          // points into SP; cast to int* or float* on write
    float default_val;  // snapshot of SP default at registration time
    void (*on_set)();   // called after value is written; nullptr if none
};

inline const std::vector<TunableParam>& tunable_params() {
    // clang-format off
    static const std::vector<TunableParam> params = {
        // name          type                 ptr                     default
        {"AspWindow",    TunableParam::INT,   &SP.asp_window,         (float)SP.asp_window,    nullptr},
        {"AspDivisor",   TunableParam::INT,   &SP.asp_divisor,        (float)SP.asp_divisor,   nullptr},
        {"AspDeltaDiv",  TunableParam::INT,   &SP.asp_delta_div,      (float)SP.asp_delta_div, nullptr},
        {"RfpMargin",    TunableParam::FLOAT, &SP.rfp_margin,         SP.rfp_margin,           nullptr},
        {"RfpDepth",     TunableParam::INT,   &SP.rfp_depth,          (float)SP.rfp_depth,     nullptr},
        {"NmpBase",      TunableParam::FLOAT, &SP.nmp_base,           SP.nmp_base,             nullptr},
        {"NmpDivisor",   TunableParam::FLOAT, &SP.nmp_divisor,        SP.nmp_divisor,          nullptr},
        {"LmrBase",      TunableParam::FLOAT, &SP.lmr_base,           SP.lmr_base,             init_search_tables},
        {"LmrDivisor",   TunableParam::FLOAT, &SP.lmr_divisor,        SP.lmr_divisor,          init_search_tables},
        {"LmrMoveMin",   TunableParam::INT,   &SP.lmr_move_min,       (float)SP.lmr_move_min,  nullptr},
        {"HistPrune",    TunableParam::INT,   &SP.hist_prune,         (float)SP.hist_prune,    nullptr},
        {"HistBonusMul", TunableParam::FLOAT, &SP.hist_bonus_mul,     SP.hist_bonus_mul,       nullptr},
        // Time management
        {"TmSoftFrac",   TunableParam::FLOAT, &SP.tm_soft_multiplier, SP.tm_soft_multiplier,   nullptr},
        {"TmHardMul",    TunableParam::FLOAT, &SP.tm_hard_multiplier, SP.tm_hard_multiplier,   nullptr},
        {"TmPvFloor",    TunableParam::FLOAT, &SP.tm_pv_floor,        SP.tm_pv_floor,          nullptr},
        {"TmPvBase",     TunableParam::FLOAT, &SP.tm_pv_base,         SP.tm_pv_base,           nullptr},
        {"TmPvDecay",    TunableParam::FLOAT, &SP.tm_pv_decay,        SP.tm_pv_decay,          nullptr},
    };
    // clang-format on
    return params;
}

// Emits "option name ... type spin/string ..." for each SPSA param.
inline void print_uci_options() {
    for (const auto& p : tunable_params()) {
        if (p.type == TunableParam::INT) {
            int def = static_cast<int>(p.default_val);
            printf("option name %-16s type spin   default %d min %d max %d\n", p.name, def, (int)(def * SP_LO),
                   (int)(def * SP_HI));
        } else {
            printf("option name %-16s type string default %.2f\n", p.name, p.default_val);
        }
    }
}

// Applies a setoption name/value pair. Returns true if the name matched.
inline bool set_uci_option(const std::string& name, const std::string& value) {
    if (value.empty()) return false;
    for (const auto& p : tunable_params()) {
        if (name == p.name) {
            try {
                if (p.type == TunableParam::INT)
                    *static_cast<int*>(p.ptr) = std::stoi(value);
                else
                    *static_cast<float*>(p.ptr) = std::stof(value);
            } catch (...) {
            }
            if (p.on_set) p.on_set();
            return true;
        }
    }
    return false;
}

// Prints SPSA CSV block: name, type, default, min, max, c_end, r_end
inline void print_spsa_csv() {
    for (const auto& p : tunable_params()) {
        float lo = p.default_val * SP_LO;
        float hi = p.default_val * SP_HI;
        float c  = (p.type == TunableParam::INT) ? std::max(p.default_val * 0.05f, 0.5f) : p.default_val * 0.05f;
        if (p.type == TunableParam::INT) {
            printf("%s, int, %d, %d, %d, %.4f, 0.002\n", p.name, (int)p.default_val, (int)lo, (int)hi, c);
        } else {
            printf("%s, float, %.2f, %.2f, %.2f, %.4f, 0.002\n", p.name, p.default_val, lo, hi, c);
        }
    }
}
