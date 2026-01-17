#pragma once

#include "../../global/include/bitboard.h"
#include "../../global/include/board.h"

inline int gamestage(const Board &board)
{
    int phase = 0;

    phase += countBits(board.pieces[WHITE][KNIGHT]) * 1;
    phase += countBits(board.pieces[WHITE][BISHOP]) * 1;
    phase += countBits(board.pieces[WHITE][ROOK]) * 2;
    phase += countBits(board.pieces[WHITE][QUEEN]) * 4;

    phase += countBits(board.pieces[BLACK][KNIGHT]) * 1;
    phase += countBits(board.pieces[BLACK][BISHOP]) * 1;
    phase += countBits(board.pieces[BLACK][ROOK]) * 2;
    phase += countBits(board.pieces[BLACK][QUEEN]) * 4;

    if (phase > 24)
        phase = 24;
    return phase;
}