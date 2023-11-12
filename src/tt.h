#pragma once

#include "types.h"

// 8192 MBS
#define MAXHASH 8192

enum : uint8_t { FLAG_NONE, FLAG_BETA, FLAG_ALPHA, FLAG_EXACT };

struct TTEntry {
    uint16_t key  = 0;
    int16_t score = 0;
    int16_t eval  = 0;
    uint8_t depth = 0;
    uint8_t flag  = FLAG_NONE;
    Move move     = Move::NO_MOVE;
};

class TranspositionTable {
   private:
    std::vector<TTEntry> entries;

   public:
    void Initialize(int usersize);
    void store(U64 key, uint8_t f, Move move, uint8_t depth, int score, int eval);
    TTEntry &probe_entry(U64 key, bool &ttHit);
    Move probe_move(U64 key);
    void prefetch_tt(const U64 key);
    void clear();
};

static inline void prefetch(const void *addr) {
#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
    _mm_prefetch((char *)addr, _MM_HINT_T0);
#else
    __builtin_prefetch(addr);
#endif
}

static inline uint32_t reduce_hash(uint32_t x, uint32_t N) { return ((uint64_t)x * (uint64_t)N) >> 32; }

int score_to_tt(int score, int ply);
int score_from_tt(int score, int ply);