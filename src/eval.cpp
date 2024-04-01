#include "eval.h"

#include "eval_constants.h"

using namespace chess;

#define TraceIncr(parameter)
#define TraceAdd(parameter)

Bitboard passed_pawn_mask[2][64], pawn_isolated_mask[64], outpost_mask[2];

void init_eval_tables() {
    for (int i = (int)PieceType::PAWN; i <= (int)PieceType::KING; i++) {
        for (int j = Square::SQ_A1; j <= Square::SQ_H8; j++) {
            pst[i][j] += material[i];
        }
    }

    outpost_mask[0] = attacks::MASK_RANK[4] | attacks::MASK_RANK[5] | attacks::MASK_RANK[6] | attacks::MASK_RANK[7];
    outpost_mask[1] = attacks::MASK_RANK[0] | attacks::MASK_RANK[1] | attacks::MASK_RANK[2] | attacks::MASK_RANK[3];

    for (int i = Square::SQ_A1; i <= Square::SQ_H8; i++) {
        Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(Square(i))];

        pawn_isolated_mask[i] = attacks::shift<Direction::EAST>(file) | attacks::shift<Direction::WEST>(file);

        passed_pawn_mask[0][i] = file | attacks::shift<Direction::EAST>(file) | attacks::shift<Direction::WEST>(file);
        passed_pawn_mask[1][i] = passed_pawn_mask[0][i];

        while (passed_pawn_mask[0][i] & (1ULL << i)) {
            passed_pawn_mask[0][i] = attacks::shift<Direction::NORTH>(passed_pawn_mask[0][i]);
        }
        while (passed_pawn_mask[1][i] & (1ULL << i)) {
            passed_pawn_mask[1][i] = attacks::shift<Direction::SOUTH>(passed_pawn_mask[1][i]);
        }
    }
}

// Get relative position of square based on color
template <Color c>
Square black_relative_square(Square &sq) {
    return (c == Color::WHITE) ? sq ^ 56 : sq;
}
template <Color c>
Square white_relative_square(Square &sq) {
    return (c == Color::BLACK) ? sq ^ 56 : sq;
}

// Get a bitboard with all pawn attacks based on pawn location and movement direction
template <Color c>
Bitboard get_pawn_attacks(Bitboard &pawns) {
    return attacks::pawnLeftAttacks<c>(pawns) | attacks::pawnRightAttacks<c>(pawns);
}

template <Color c>
int eval_pawn(EvalInfo &info, const Board &board) {
    int score = 0, count = 0;
    Bitboard bb = board.pieces(PieceType::PAWN, c);

    // Init useful bitboards
    Bitboard phalanx_pawns    = bb & attacks::shift<Direction::WEST>(bb);
    Bitboard pawn_attacks     = get_pawn_attacks<c>(bb);
    info.pawn_attacks[(int)c] = pawn_attacks;

    // Penalty for doubled pawns
    count = builtin::popcount(bb & attacks::shift<Direction::NORTH>(bb));
    score += pawn_doubled[0] * count;
    TraceAdd(pawn_doubled[0]);

    count = builtin::popcount(bb & attacks::shift<Direction::NORTH>(attacks::shift<Direction::NORTH>(bb)));
    score += pawn_doubled[1] * count;
    TraceAdd(pawn_doubled[1]);

    // Bonus for pawns protecting pawns
    count = builtin::popcount(bb & get_pawn_attacks<~c>(bb));
    score += pawn_support * count;
    TraceAdd(pawn_support);

    // Bonus for phalanx pawns
    while (phalanx_pawns) {
        Square sq = builtin::poplsb(phalanx_pawns);

        score += pawn_phalanx[white_relative_square<c>(sq) >> 3];
        TraceIncr(pawn_phalanx[white_relative_square<c>(sq) >> 3]);
    }

    while (bb) {
        Square sq = builtin::poplsb(bb);

        // Penalty is pawn is isolated
        if (!(pawn_isolated_mask[sq] & info.pawn[(int)c])) {
            score += pawn_isolated;
            TraceIncr(pawn_isolated);
        }

        // Bonus if pawn is passed
        if (!(passed_pawn_mask[(int)c][sq] & info.pawn[(int)~c])) {
            int protectors = builtin::popcount(info.pawn[(int)c] & attacks::pawn(~c, sq));

            // Bonus if passed pawn is protected by pawn
            score += pawn_passed[protectors][white_relative_square<c>(sq) >> 3];
            TraceIncr(pawn_passed[protectors][white_relative_square<c>(sq) >> 3]);
        }

        score += pst[0][black_relative_square<c>(sq)];
        TraceIncr(pst[0][black_relative_square<c>(sq)]);
        TraceIncr(material[0]);
    }

    return score;
}

template <Color c, PieceType p>
int eval_piece(EvalInfo &info, const Board &board) {
    int score = 0, count = 0;
    Bitboard bb = board.pieces(p, c);

    // Init useful directions
    // const Direction UP   = c == Color::WHITE ? Direction::NORTH : Direction::SOUTH;
    const Direction DOWN = c == Color::WHITE ? Direction::SOUTH : Direction::NORTH;

    // Increase gamephase
    info.gamephase += phase_values[(int)p] * builtin::popcount(bb);

    // Bishop pair bonus
    if (p == PieceType::BISHOP && (bb & (bb - 1))) {
        score += bishop_pair;
        TraceIncr(bishop_pair);
    }

    // Bonus for minor piece behind pawn
    if (p == PieceType::KNIGHT || p == PieceType::BISHOP) {
        count = builtin::popcount(bb & attacks::shift<DOWN>(info.pawn[(int)c]));
        score += minor_behind_pawn * count;
        TraceAdd(minor_behind_pawn);

        // Bonus for knight/bishop outposts
        count = builtin::popcount(bb & info.pawn_attacks[(int)c] & outpost_mask[(int)c]);
        score += outpost * count;
        TraceAdd(outpost);
    }

    while (bb) {
        Square sq = builtin::poplsb(bb);

        // Open and Semi-Open file bonus
        if (p == PieceType::ROOK) {
            Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(sq)];
            if (!(file & info.pawn[(int)c])) {
                if (!(file & info.pawn[(int)~c])) {
                    score += open_file;
                    TraceIncr(open_file);
                } else {
                    score += semi_open_file;
                    TraceIncr(semi_open_file);
                }
            }
        }

        // Penalty is piece is attacked by pawn
        if (info.pawn[(int)~c] & attacks::pawn(c, sq)) {
            score += attacked_by_pawn[(int)p];
            TraceIncr(attacked_by_pawn[(int)p]);
        }

        // Get move bb for piece
        Bitboard moves = 0;
        if (p == PieceType::KNIGHT)
            moves = attacks::knight(sq);
        else if (p == PieceType::BISHOP)
            moves = attacks::bishop(sq, board.occ());
        else if (p == PieceType::ROOK)
            moves = attacks::rook(sq, board.occ());
        else if (p == PieceType::QUEEN)
            moves = attacks::queen(sq, board.occ());

        // Bonus/penalty for number of moves per piece
        score += mobility[(int)p - 1][builtin::popcount(moves & ~board.us(c) & ~info.pawn_attacks[(int)~c])];
        TraceIncr(mobility[(int)p - 1][builtin::popcount(moves & ~board.us(c) & ~info.pawn_attacks[(int)~c])]);

        score += pst[(int)p][black_relative_square<c>(sq)];
        TraceIncr(pst[(int)p][black_relative_square<c>(sq)]);
        TraceIncr(material[(int)p]);
    }

    return score;
}

template <Color c>
int eval_king(EvalInfo &info, const Board &board) {
    int score = 0, count = 0;
    Bitboard bb    = board.pieces(PieceType::KING, c);
    Square king_sq = builtin::poplsb(bb);

    // Init useful bitboards
    Bitboard moves = attacks::queen(king_sq, board.occ());

    // Bonus/penalty for number of squares king could be attacked from
    score += king_open[builtin::popcount(moves & ~board.us(c) & ~info.pawn_attacks[(int)~c])];
    TraceIncr(king_open[builtin::popcount(moves & ~board.us(c) & ~info.pawn_attacks[(int)~c])]);

    // Bonus/penalty if king threatens enemy pawn
    if (attacks::king(king_sq) & info.pawn[(int)~c]) {
        score += king_att_pawn;
        TraceIncr(king_att_pawn);
    }

    // Bonus for pawn sheltering king
    count = builtin::popcount(passed_pawn_mask[(int)c][king_sq] & info.pawn[(int)c]);
    score += king_shelter * count;
    TraceAdd(king_shelter);

    score += pst[5][black_relative_square<c>(king_sq)];
    TraceIncr(pst[5][black_relative_square<c>(king_sq)]);

    return score;
}

int eval_pieces(EvalInfo &info, const Board &board) {
    return eval_pawn<Color::WHITE>(info, board) - eval_pawn<Color::BLACK>(info, board) +

           eval_piece<Color::WHITE, PieceType::KNIGHT>(info, board) +
           eval_piece<Color::WHITE, PieceType::BISHOP>(info, board) +
           eval_piece<Color::WHITE, PieceType::ROOK>(info, board) +
           eval_piece<Color::WHITE, PieceType::QUEEN>(info, board) -

           eval_piece<Color::BLACK, PieceType::KNIGHT>(info, board) -
           eval_piece<Color::BLACK, PieceType::BISHOP>(info, board) -
           eval_piece<Color::BLACK, PieceType::ROOK>(info, board) -
           eval_piece<Color::BLACK, PieceType::QUEEN>(info, board) +

           eval_king<Color::WHITE>(info, board) - eval_king<Color::BLACK>(info, board);
}

void init_eval_info(EvalInfo &info, const Board &board) {
    // Add pawn bb to eval info
    info.pawn[0]         = board.pieces(PieceType::PAWN, Color::WHITE);
    info.pawn[1]         = board.pieces(PieceType::PAWN, Color::BLACK);
    info.pawn_attacks[0] = get_pawn_attacks<Color::WHITE>(info.pawn[0]);
    info.pawn_attacks[1] = get_pawn_attacks<Color::BLACK>(info.pawn[1]);
}

double endgame_scale(EvalInfo &info, int score) {
    // Divide the endgame score if the stronger side doesn't have many pawns left
    int num_missing_stronger_pawns = 8 - builtin::popcount(info.pawn[score < 0]);
    return (128 - num_missing_stronger_pawns * num_missing_stronger_pawns) / 128.0;
}

int evaluate(const Board &board) {
    // Check for draw by insufficient material
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    init_eval_info(info, board);

    int score = eval_pieces(info, board);

    int gamephase = std::min(info.gamephase, 24);

    score = (mg_score(score) * gamephase + eg_score(score) * (24 - gamephase) * endgame_scale(info, score)) / 24;

    return (board.sideToMove() == Color::WHITE ? score : -score);
}