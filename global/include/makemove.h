#pragma once

#include "./board.h"
#include "./bitboard.h"
#include "./movelist.h"
#include "../../tables/include/zobrist.h"
#include <iostream>

void makemove(Board &board, const Move &move);
void undomove(Board &board);

int getPieceTypeOnSquare(const Board &board, int sq);

inline void updateCastlingRights(Board &board, const Move &move)
{
    const Color side = board.sideToMove;
    const Color enemy = (side == WHITE ? BLACK : WHITE);

    // --- If the king moves, both castling rights are lost ---
    if (move.piece == KING)
    {
        if (side == WHITE) {
            board.wks = false;
            board.wqs = false;
        } else {
            board.bks = false;
            board.bqs = false;
        }
    }

    // --- If a rook moves, remove the corresponding castling right ---
    if (move.piece == ROOK)
    {
        if (side == WHITE)
        {
            if (move.from == 0)  board.wqs = false; // rook on a1 moved
            if (move.from == 7)  board.wks = false; // rook on h1 moved
        }
        else
        {
            if (move.from == 56) board.bqs = false; // rook on a8 moved
            if (move.from == 63) board.bks = false; // rook on h8 moved
        }
    }

    // --- If a rook is captured, remove enemy castling rights ---
    if (move.captured && !move.en_passant)
    {
        if (move.to == 0)  board.wqs = false; // rook on a1 captured
        if (move.to == 7)  board.wks = false; // rook on h1 captured
        if (move.to == 56) board.bqs = false; // rook on a8 captured
        if (move.to == 63) board.bks = false; // rook on h8 captured
    }

    // --- Update the bitmask castlingRights to match the flags ---
    board.castlingRights = 0;
    if (board.wks) board.castlingRights |= WHITE_KINGSIDE;
    if (board.wqs) board.castlingRights |= WHITE_QUEENSIDE;
    if (board.bks) board.castlingRights |= BLACK_KINGSIDE;
    if (board.bqs) board.castlingRights |= BLACK_QUEENSIDE;
}
