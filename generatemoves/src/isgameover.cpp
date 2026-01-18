#include "../include/isgameover.h"

bool insufficiant_material(const Board &board)
{
    if (board.pieces[WHITE][PAWN] || board.pieces[BLACK][PAWN])
        return false;
    if (board.pieces[WHITE][ROOK] || board.pieces[BLACK][ROOK] || board.pieces[WHITE][QUEEN] || board.pieces[BLACK][QUEEN])
        return false;

    int whiteMinor = __builtin_popcountll(board.pieces[WHITE][KNIGHT]) + __builtin_popcountll(board.pieces[WHITE][BISHOP]);
    int blackMinor = __builtin_popcountll(board.pieces[BLACK][KNIGHT]) + __builtin_popcountll(board.pieces[BLACK][BISHOP]);

    if (whiteMinor > 1 || blackMinor > 1)
    {
        return false;
    }

    if (whiteMinor == 0 && blackMinor == 0)
    {
        return true;
    }

    if (whiteMinor == 1 && blackMinor == 0)
        return true;
    if (blackMinor == 1 && whiteMinor == 0)
        return true;
    return false;
}

bool isCheck(const Board &board, Color side)
{
    Color enemy = (side == WHITE ? BLACK : WHITE);

    Bitboard kingBB = board.pieces[side][KING];
    int kingSq = __builtin_ctzll(kingBB);

    // Knight
    if (knightAttacks[kingSq] & board.pieces[enemy][KNIGHT])
        return true;
    if (kingAttacks[kingSq] & board.pieces[enemy][KING])
        return true;

    if (side == WHITE)
    {
        if (pawnAttacksBlack[kingSq] & board.pieces[enemy][PAWN])
            return true;
    }
    else
    {
        if (pawnAttacksWhite[kingSq] & board.pieces[enemy][PAWN])
            return true;
    }

    Bitboard bishopAtt = getBishopAttacks(kingSq, board.occupiedAll);
    if (bishopAtt & (board.pieces[enemy][BISHOP] | board.pieces[enemy][QUEEN]))
    {
        return true;
    }
    Bitboard rookAtt = getRookAttacks(kingSq, board.occupiedAll);
    if (rookAtt & (board.pieces[enemy][ROOK] | board.pieces[enemy][QUEEN]))
        return true;
    return false;
}

GameResult isGameOver(Board &board)
{
    // 50 Move rule
    if (board.halfmoveclock >= 100)
    {
        return DRAW_50_MOVES;
    }

    // Repeat
    int repetitions = 1;
    for (int i = board.historySize - 2; i >= 0; i -= 2)
    {
        if (board.history[i].zobristKey == board.zobristKey)
        {
            repetitions++;
        }
        if (repetitions >= 3)
        {
            return DRAW_REPETITION;
        }
    }

    // Insufficiant Material
    if (insufficiant_material(board))
        return DRAW_INSUFFICIENT_MATERIAL;

    MoveList movelist = generateMoves(board);
    if (movelist.count2 == 0)
    {
        if (isCheck(board, board.sideToMove)) {
            return (board.sideToMove == WHITE ? BLACK_WINS : WHITE_WINS);
        } else {
            return DRAW_STALEMATE;
        }
    }
    return GAME_ONGOING;
}