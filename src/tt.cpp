#include "tt.h"

void TranspositionTable::Initialize(int MB) {
    clear();
    this->entries.resize((MB * 1024 * 1024) / sizeof(TTEntry), TTEntry());
    std::fill(entries.begin(), entries.end(), TTEntry());

    std::cout << "Transposition Table Initialized with " << entries.size() << " entries (" << MB << "MB)" << std::endl;
}

void TranspositionTable::store(U64 key, uint8_t f, Move move, uint8_t depth, int score, int eval) {
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

TTEntry& TranspositionTable::probe_entry(U64 key, bool& ttHit) {
    TTEntry& entry = entries[reduce_hash(key, entries.size())];
    ttHit          = (static_cast<uint16_t>(key) == entry.key);
    return entry;
}

Move TranspositionTable::probe_move(U64 key) {
    TTEntry& entry = entries[reduce_hash(key, entries.size())];

    if (static_cast<uint16_t>(key) == entry.key) {
        return entry.move;
    }

    return Move::NO_MOVE;
}

void TranspositionTable::prefetch_tt(const U64 key) { prefetch(&(entries[reduce_hash(key, entries.size())])); }

void TranspositionTable::clear() { entries.clear(); }

int score_to_tt(int score, int ply) {
    if (score >= MATE_IN_MAX) {
        return score - ply;
    } else if (score <= MATED_IN_MAX) {
        return score + ply;
    }

    return score;
}

int score_from_tt(int score, int ply) {
    if (score >= MATE_IN_MAX) {
        return score - ply;
    } else if (score <= MATED_IN_MAX) {
        return score + ply;
    }

    return score;
}