#pragma once

#include "./board.h"
#include "./bitboard.h"
#include "./movelist.h"

void makemove(Board &board, const Move &move);
void undomove(Board &board);

int getPieceTypeOnSquare(const Board &board, int sq);

inline void updateCatlingRights(Board &board, const Move &move)
{
    const int from = move.from;
    const int to = move.to;
    const Color side = board.sideToMove;

    if (move.piece == KING)
    {
        if (side == WHITE)
        {
            board.castlingRights &= ~0b0011;
        }
        else
        {
            board.castlingRights &= ~0b1100;
        }
    }

    if (move.piece == ROOK)
    {
        if (side == WHITE)
        {
            if (from == 0)
                board.castlingRights &= ~0b0010;
            if (from == 7)
                board.castlingRights &= ~0b0001;
        }
        else
        {
            if (from == 56)
                board.castlingRights &= ~0b1000;
            if (from == 63)
                board.castlingRights &= ~0b0100;
        }
    }

    if (move.captured && !move.en_passant)
    {
        if (to == 0)
            board.castlingRights &= ~0b0010;
        if (to == 7)
            board.castlingRights &= ~0b0001;
        if (to == 56)
            board.castlingRights &= ~0b1000;
        if (to == 63)
            board.castlingRights &= ~0b0100;
    }
}