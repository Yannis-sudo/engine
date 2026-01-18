#pragma once

#include "../../global/include/board.h"
#include "./attacks.h"
#include "./pawnattacks.h"
#include <iostream>
#include "../../global/include/movelist.h"
#include "./attacks.h"
#include "./lookup.h"
#include "../../global/include/makemove.h"
#include <thread>
#include <vector>
#include "./castling.h"

MoveList generateMoves(Board &board);

inline bool isSquareAttacked(int sq, const Board &board, Color attackingSide) noexcept
{
    if (knightAttacks[sq] & board.pieces[attackingSide][KNIGHT])
        return true; // KNIGHT
    if (kingAttacks[sq] & board.pieces[attackingSide][KING])
        return true; // KING
    if (attackingSide == WHITE)
    {
        if (pawnAttacksWhite[sq] & board.pieces[attackingSide][PAWN])
            return true; // PAWN WHITE
    }
    else
    {
        if (pawnAttacksBlack[sq] & board.pieces[attackingSide][PAWN])
            return true; // PAWN BLACK
    }
    const Bitboard bishopAtt = getBishopAttacks(sq, board.occupiedAll);
    if (bishopAtt & (board.pieces[attackingSide][BISHOP] | board.pieces[attackingSide][QUEEN]))
        return true; // BISHOP / QUEEN

    // ROOK / QUEEN
    const Bitboard rookAtt = getRookAttacks(sq, board.occupiedAll);
    if (rookAtt & (board.pieces[attackingSide][ROOK] | board.pieces[attackingSide][QUEEN]))
        return true;
    return false;
}