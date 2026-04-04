#pragma once

inline bool moveExists(Board& board, Move move) {
    Movelist list;
    movegen::legalmoves(list, board);

    return std::find(list.begin(), list.end(), move) != list.end();
}

inline void get_pv_hash(SearchThread& st, std::vector<uint64_t>& positions) {
    if (positions.size() >= MAX_PLY) return;
    if (st.board.isRepetition(1) || st.board.isHalfMoveDraw()) return;

    auto pv_move = table->probe_move(st.board.hash());

    if (pv_move != Move::NO_MOVE && moveExists(st.board, pv_move)) {
        for (auto& pos : positions)
            if (pos == st.board.hash()) return;

        std::cout << " " << uci::moveToUci(pv_move);
        positions.push_back(st.board.hash());

        st.make_move(pv_move);
        get_pv_hash(st, positions);
        st.unmake_move(pv_move);
    }

    return;
}

inline void get_pv(SearchThread& st, std::vector<uint64_t>& positions, Move best_move) {
    assert(best_move != Move::NO_MOVE);

    std::cout << " " << uci::moveToUci(best_move);
    positions.push_back(st.board.hash());

    st.make_move(best_move);
    get_pv_hash(st, positions);
    st.unmake_move(best_move);

    return;
}