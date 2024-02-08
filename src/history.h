#pragma once

#include "search.h"

using namespace chess;

inline int &get_history(SearchThread &st, Move move) { return st.history[(int)st.board.at(move.from())][move.to()]; }

inline void history_bonus(int &cur, int bonus) { cur += 32 * bonus - cur * abs(bonus) / 512; }

inline void update_history(SearchThread &st, Move good, Movelist &moves, int bonus) {
    history_bonus(get_history(st, good), bonus);

    for (auto move : moves)
        if (move != good) history_bonus(get_history(st, move), -bonus);
}