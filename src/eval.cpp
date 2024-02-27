#include "eval.h"

#include "eval_constants.h"

using namespace chess;

Bitboard passed_pawn_mask[2][64];

void init_eval_tables() {
    for (int i = (int)PieceType::PAWN; i <= (int)PieceType::KING; i++) {
        for (int j = Square::SQ_A1; j <= Square::SQ_H8; j++) {
            pst[i][j] += material[i];
        }
    }

    for (int i = Square::SQ_A1; i <= Square::SQ_H8; i++) {
        Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(Square(i))];

        passed_pawn_mask[0][i] = file | attacks::shift<Direction::EAST>(file) | attacks::shift<Direction::WEST>(file);
        passed_pawn_mask[1][i] = passed_pawn_mask[0][i];

        while (passed_pawn_mask[0][i] & (1 << i)) {
            passed_pawn_mask[0][i] = attacks::shift<Direction::NORTH>(passed_pawn_mask[0][i]);
        }
        while (passed_pawn_mask[1][i] & (1 << i)) {
            passed_pawn_mask[1][i] = attacks::shift<Direction::SOUTH>(passed_pawn_mask[1][i]);
        }
    }
}

// Get relative position of square based on color
template <Color c>
Square black_relative_square(Square sq) {
    return (c == Color::WHITE) ? sq ^ 56 : sq;
}
template <Color c>
Square white_relative_square(Square sq) {
    return (c == Color::BLACK) ? sq ^ 56 : sq;
}

// Get a bitboard with all pawn attacks based on pawn location and movement direction
template <Direction D>
Bitboard get_pawn_attacks(Bitboard &pawns) {
    Bitboard shifted = attacks::shift<D>(pawns);
    return attacks::shift<Direction::WEST>(shifted) | attacks::shift<Direction::EAST>(shifted);
}

template <Color c>
int eval_pawn(EvalInfo &info, const Board &board) {
    int score   = 0;
    Bitboard bb = board.pieces(PieceType::PAWN, c);

    // Init useful directions
    const Direction UP = c == Color::WHITE ? Direction::NORTH : Direction::SOUTH;

    // Init friendly pawn attacks
    info.pawn_attacks[(int)c] = get_pawn_attacks<UP>(bb);
    Bitboard pawn_phalanx     = bb & attacks::shift<Direction::WEST>(bb);

    // Penalty for doubled pawns
    score +=
        doubled_pawn * builtin::popcount(bb & (attacks::shift<UP>(bb) | attacks::shift<UP>(attacks::shift<UP>(bb))));

    // Bonus for phalanx pawns
    while (pawn_phalanx) {
        Square sq = builtin::poplsb(pawn_phalanx);

        score += phalanx_pawns[(int)utils::squareRank(white_relative_square<c>(sq))];
    }

    while (bb) {
        Square sq = builtin::poplsb(bb);

        // Bonus if pawn is protected by pawn
        if (info.pawn_attacks[(int)c] & (1ULL << sq)) {
            score += protected_by_pawn[0];
        }

        // Bonus if pawn is passed
        if (!(passed_pawn_mask[(int)c][sq] & info.pawn[(int)~c])) {
            score += passed_pawns[(int)utils::squareRank(white_relative_square<c>(sq))];
        }

        score += pst[0][black_relative_square<c>(sq)];
    }

    return score;
}

template <Color c, PieceType p>
int eval_piece(EvalInfo &info, const Board &board) {
    int score   = 0;
    Bitboard bb = board.pieces(p, c);
    info.gamephase += phase_values[(int)p] * builtin::popcount(bb);

    // Bishop pair bonus
    if (p == PieceType::BISHOP && (bb & (bb - 1))) {
        score += bishop_pair;
    }

    while (bb) {
        Square sq = builtin::poplsb(bb);

        // Open and Semi-Open file bonus
        if ((int)p >= 3) {
            Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(sq)];
            if (!(file & info.pawn[(int)c])) {
                if (!(file & info.pawn[(int)~c])) {
                    score += open_file[(int)p - 3];
                } else {
                    score += semi_open_file[(int)p - 3];
                }
            }
        }

        // Bonus if piece is protected by pawn
        if (info.pawn_attacks[(int)c] & (1ULL << sq)) {
            score += protected_by_pawn[(int)p];
        }

        // Penalty is piece is attacked by pawn
        if (info.pawn_attacks[(int)~c] & (1ULL << sq)) {
            score += attacked_by_pawn[c == board.sideToMove()];
        }

        // Get move bb for piece
        Bitboard moves = 0;
        if (p == PieceType::KNIGHT)
            moves = attacks::knight(sq);
        else if (p == PieceType::BISHOP)
            moves = attacks::bishop(sq, board.occ());
        else if (p == PieceType::ROOK)
            moves = attacks::rook(sq, board.occ());
        else if (p == PieceType::QUEEN || p == PieceType::KING)
            moves = attacks::queen(sq, board.occ());

        // Bonus/penalty for number of moves per piece
        score += mobility[(int)p - 1][builtin::popcount(moves & ~board.us(c) & ~info.pawn_attacks[(int)~c])];

        score += pst[(int)p][black_relative_square<c>(sq)];
    }

    return score;
}

void eval_pieces(EvalInfo &info, const Board &board) {
    // Add pawn bb to eval info
    info.pawn[(int)Color::WHITE] = board.pieces(PieceType::PAWN, Color::WHITE);
    info.pawn[(int)Color::BLACK] = board.pieces(PieceType::PAWN, Color::BLACK);

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
    // Divide the endgame score if the stronger side doesn't have many pawns left
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