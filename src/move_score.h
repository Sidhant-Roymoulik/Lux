#pragma once

#include "history.h"

using namespace chess;

enum MoveGenStage {
    TT_MOVE  = INT16_MAX,
    CAPTURE  = 20000,
    KILLER_1 = 19000,
    KILLER_2 = 18000,
};

// Most Valuable Victim / Least Valuable Attacker weights indexed by PieceType [pawn..king]
constexpr int16_t mvv_lva[6] = {10, 32, 33, 50, 90, 0};

inline void sort_moves(Movelist& moves, int i) {
    int best = i;
    for (int j = i + 1; j < moves.size(); j++) {
        if (moves[j].score() > moves[best].score()) best = j;
    }
    std::swap(moves[i], moves[best]);
}

// q_search_mode = true: skip killer moves and promotions (q-search only needs captures).
// if constexpr eliminates the dead branch at compile time — zero runtime overhead.
template <bool q_search_mode = false>
inline void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = static_cast<int>(st.board.at<PieceType>(moves[i].to()));
        int attacker = static_cast<int>(st.board.at<PieceType>(moves[i].from()));

        if (moves[i] == tt_move) {
            moves[i].setScore(MoveGenStage::TT_MOVE);

        } else if constexpr (!q_search_mode) {
            if (moves[i].typeOf() == Move::PROMOTION)
                moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[static_cast<int>(moves[i].promotionType())]);
            else if (st.board.isCapture(moves[i]))
                moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[victim] - mvv_lva[attacker]);
            else if (moves[i] == ss->killers[0])
                moves[i].setScore(MoveGenStage::KILLER_1);
            else if (moves[i] == ss->killers[1])
                moves[i].setScore(MoveGenStage::KILLER_2);
            else
                moves[i].setScore(get_history(st, moves[i]));

        } else {
            // Promotions scored as captures via mvv_lva; no separate case needed in q-search
            if (st.board.isCapture(moves[i]))
                moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[victim] - mvv_lva[attacker]);
            else
                moves[i].setScore(get_history(st, moves[i]));
        }
    }
}
