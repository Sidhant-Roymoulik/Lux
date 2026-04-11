#pragma once

inline int& get_history(SearchThread& st, Move move) {
    return st.history[static_cast<int>(st.board.at(move.from()))][move.to().index()];
}

// cur += 32*bonus - cur*|bonus|/512
// The subtracted term acts as a drag that prevents scores escaping ±16384,
// keeping history values comparable across the search tree.
inline void history_bonus(int& cur, int bonus) { cur += 32 * bonus - cur * abs(bonus) / 512; }

inline void update_history(SearchThread& st, Move good, Movelist& moves, int bonus) {
    history_bonus(get_history(st, good), bonus);

    for (auto move : moves)
        if (move != good) history_bonus(get_history(st, move), -bonus);
}
