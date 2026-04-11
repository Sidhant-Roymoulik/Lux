#pragma once

inline bool moveExists(const Board& board, Move move) {
    Movelist list;
    movegen::legalmoves(list, board);

    return std::find(list.begin(), list.end(), move) != list.end();
}

inline void print_pv_from_tt(SearchThread& st, int ply) {
    if (ply >= MAX_PLY) return;
    if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return;

    auto pv_move = table->probe_move(st.board.hash());

    if (pv_move != Move::NO_MOVE && moveExists(st.board, pv_move)) {
        std::cout << " " << uci::moveToUci(pv_move);

        st.make_move(pv_move);
        print_pv_from_tt(st, ply + 1);
        st.unmake_move(pv_move);
    }
}

inline void get_pv(SearchThread& st, Move best_move) {
    assert(best_move != Move::NO_MOVE);

    std::cout << " " << uci::moveToUci(best_move);

    st.make_move(best_move);
    print_pv_from_tt(st, 1);
    st.unmake_move(best_move);
}