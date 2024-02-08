#pragma once

#include "search.h"

inline bool moveExists(Board& board, Move move);
void get_pv_hash(SearchThread& st, std::vector<U64>& positions);
void get_pv(SearchThread& st, std::vector<U64>& positions, Move best_move);