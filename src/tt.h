#pragma once

#include "types.h"

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

    static inline uint32_t reduce_hash(uint32_t x, uint32_t N) { return ((uint64_t)x * (uint64_t)N) >> 32; }

    static inline void prefetch(const void* addr) {
#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
        _mm_prefetch((char*)addr, _MM_HINT_T0);
#else
        __builtin_prefetch(addr);
#endif
    }

   public:
    void clear() { entries.clear(); }

    void Initialize(int MB) {
        clear();
        this->entries.resize((MB * 1024 * 1024) / sizeof(TTEntry), TTEntry());
        std::fill(entries.begin(), entries.end(), TTEntry());

        std::cout << "Transposition Table Initialized with " << entries.size() << " entries (" << MB << "MB)"
                  << std::endl;
    }

    void store(U64 key, uint8_t f, Move move, uint8_t depth, int score, int eval) {
        TTEntry& entry = entries[reduce_hash(key, entries.size())];

        if (move != Move::NO_MOVE || static_cast<uint16_t>(key) != entry.key) {
            entry.move = move;
        }

        if (f == FLAG_EXACT || static_cast<uint16_t>(key) != entry.key || depth > entry.depth) {
            entry.key   = static_cast<uint16_t>(key);
            entry.flag  = f;
            entry.move  = move;
            entry.depth = depth;
            entry.score = (int16_t)score;
            entry.eval  = (int16_t)eval;
        }
    }

    TTEntry& probe_entry(U64 key, bool& ttHit) {
        TTEntry& entry = entries[reduce_hash(key, entries.size())];
        ttHit          = (static_cast<uint16_t>(key) == entry.key);
        return entry;
    }

    Move probe_move(U64 key) {
        TTEntry& entry = entries[reduce_hash(key, entries.size())];

        if (static_cast<uint16_t>(key) == entry.key) {
            return entry.move;
        }

        return Move::NO_MOVE;
    }

    void prefetch_tt(const U64 key) { prefetch(&(entries[reduce_hash(key, entries.size())])); }
};

inline int score_to_tt(int score, int ply) {
    if (score >= MATE_IN_MAX) {
        return score - ply;
    } else if (score <= MATED_IN_MAX) {
        return score + ply;
    }

    return score;
}

inline int score_from_tt(int score, int ply) {
    if (score >= MATE_IN_MAX) {
        return score - ply;
    } else if (score <= MATED_IN_MAX) {
        return score + ply;
    }

    return score;
}