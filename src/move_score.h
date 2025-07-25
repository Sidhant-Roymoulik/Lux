#pragma once

#include "history.h"

using namespace chess;

enum MoveGenStage {
    TT_MOVE  = INT16_MAX,
    CAPTURE  = 20000,
    KILLER_1 = 19000,
    KILLER_2 = 18000,
};

constexpr int16_t mvv_lva[6] = {10, 32, 33, 50, 90, 0};

inline void score_moves(SearchThread& st, SearchStack* ss, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (moves[i] == tt_move) {
            moves[i].setScore(MoveGenStage::TT_MOVE);

        } else if (moves[i].typeOf() == Move::PROMOTION) {
            moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[(int)moves[i].promotionType()]);

        } else if (st.board.isCapture(moves[i])) {
            moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[victim] - mvv_lva[attacker]);

        } else if (moves[i] == ss->killers[0]) {
            moves[i].setScore(MoveGenStage::KILLER_1);

        } else if (moves[i] == ss->killers[1]) {
            moves[i].setScore(MoveGenStage::KILLER_2);

        } else {
            moves[i].setScore(get_history(st, moves[i]));
        }
    }
}

inline void score_moves(SearchThread& st, Movelist& moves, Move tt_move) {
    for (int i = 0; i < moves.size(); i++) {
        int victim   = (int)st.board.at<PieceType>(moves[i].to());
        int attacker = (int)st.board.at<PieceType>(moves[i].from());

        if (moves[i] == tt_move) {
            moves[i].setScore(MoveGenStage::TT_MOVE);

            // } else if (moves[i].typeOf() == Move::PROMOTION) {
            //     moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[(int)moves[i].promotionType()]);

        } else if (st.board.isCapture(moves[i])) {
            moves[i].setScore(MoveGenStage::CAPTURE + mvv_lva[victim] - mvv_lva[attacker]);

        } else {
            moves[i].setScore(get_history(st, moves[i]));
        }
    }
}