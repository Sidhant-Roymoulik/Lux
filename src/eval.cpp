#include "eval.h"

#include "eval_constants.h"

using namespace chess;

void init_eval_tables() {
    for (int i = (int)PieceType::PAWN; i <= (int)PieceType::KING; i++) {
        for (int j = Square::SQ_A1; j <= Square::SQ_H8; j++) {
            pst[i][j] += material[i];
        }
    }
}

template <Color c>
int eval_pawn(EvalInfo &info, const Board &board) {
    int score   = 0;
    Bitboard bb = board.pieces(PieceType::PAWN, c);

    info.pawn[(int)c] = bb;

    while (bb) {
        Square sq = builtin::poplsb(bb);

        if (c == Color::WHITE) sq = sq ^ 56;

        score += pst[(int)PieceType::PAWN][sq];
    }

    return score;
}

template <Color c, PieceType p>
int eval_piece(EvalInfo &info, const Board &board) {
    int score   = 0;
    Bitboard bb = board.pieces(p, c);
    info.gamephase += phase_values[(int)p] * builtin::popcount(bb);

    const Direction UP_EAST = c == Color::BLACK ? Direction::NORTH_EAST : Direction::SOUTH_EAST;
    const Direction UP_WEST = c == Color::BLACK ? Direction::NORTH_WEST : Direction::SOUTH_WEST;

    Bitboard pawn_attacks = attacks::shift<UP_EAST>(info.pawn[(int)~c]) | attacks::shift<UP_WEST>(info.pawn[(int)~c]);

    if (p == PieceType::BISHOP && (bb & (bb - 1))) {
        score += bishop_pair;
    }

    while (bb) {
        Square sq = builtin::poplsb(bb);

        if ((int)p >= 3) {
            Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(sq)];
            if (!(file & info.pawn[(int)c])) {
                if (!(file & info.pawn[(int)~c])) {
                    score += open_file[(int)p];
                } else {
                    score += semi_open_file[(int)p];
                }
            }
        }

        Bitboard moves = 0;
        if (p == PieceType::KNIGHT)
            moves = attacks::knight(sq);
        else if (p == PieceType::BISHOP)
            moves = attacks::bishop(sq, board.occ());
        else if (p == PieceType::ROOK)
            moves = attacks::rook(sq, board.occ());
        else if (p == PieceType::QUEEN || p == PieceType::KING)
            moves = attacks::queen(sq, board.occ());

        score += mobility[(int)p - 1][builtin::popcount(moves & ~board.us(c) & ~pawn_attacks)];

        if (c == Color::WHITE) sq = sq ^ 56;

        score += pst[(int)p][sq];
    }

    return score;
}

void eval_pieces(EvalInfo &info, const Board &board) {
    info.score += eval_pawn<Color::WHITE>(info, board);
    info.score -= eval_pawn<Color::BLACK>(info, board);

    info.score += eval_piece<Color::WHITE, PieceType::KNIGHT>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::BISHOP>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::ROOK>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::QUEEN>(info, board);

    info.score -= eval_piece<Color::BLACK, PieceType::KNIGHT>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::BISHOP>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::ROOK>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::QUEEN>(info, board);

    info.score += eval_piece<Color::WHITE, PieceType::KING>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::KING>(info, board);
}

double endgame_scale(EvalInfo &info) {
    int num_missing_stronger_pawns = 8 - builtin::popcount(info.pawn[info.score < 0]);
    return (128 - num_missing_stronger_pawns * num_missing_stronger_pawns) / 128.0;
}

int evaluate(const Board &board) {
    // Check for draw by insufficient material
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    eval_pieces(info, board);

    info.gamephase = std::min(info.gamephase, 24);
    info.scale     = endgame_scale(info);

    int score =
        (mg_score(info.score) * info.gamephase + eg_score(info.score) * (24 - info.gamephase) * info.scale) / 24;

    return (board.sideToMove() == Color::WHITE ? score : -score);
}