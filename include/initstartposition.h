#pragma once
#include "../global/include/board.h"

Board initStartPosition()
{
    Board board{};

    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('a', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('b', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('c', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('d', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('e', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('f', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('g', 2);
    board.pieces[WHITE][PAWN] |= 1ULL << board.squareIndex('h', 2);

    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('a', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('b', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('c', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('d', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('e', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('f', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('g', 7);
    board.pieces[BLACK][PAWN] |= 1ULL << board.squareIndex('h', 7);
    
    board.pieces[WHITE][ROOK] |= 1ULL << board.squareIndex('a', 1);
    board.pieces[WHITE][ROOK] |= 1ULL << board.squareIndex('h', 1);
    board.pieces[WHITE][BISHOP] |= 1ULL << board.squareIndex('c', 1);
    board.pieces[WHITE][BISHOP] |= 1ULL << board.squareIndex('f', 1);
    board.pieces[WHITE][KNIGHT] |= 1ULL << board.squareIndex('b', 1);
    board.pieces[WHITE][KNIGHT] |= 1ULL << board.squareIndex('g', 1);
    board.pieces[WHITE][QUEEN] |= 1ULL << board.squareIndex('d', 1);
    board.pieces[WHITE][KING] |= 1ULL << board.squareIndex('e', 1);

    board.pieces[BLACK][ROOK] |= 1ULL << board.squareIndex('a', 8);
    board.pieces[BLACK][ROOK] |= 1ULL << board.squareIndex('h', 8);
    board.pieces[BLACK][BISHOP] |= 1ULL << board.squareIndex('c', 8);
    board.pieces[BLACK][BISHOP] |= 1ULL << board.squareIndex('f', 8);
    board.pieces[BLACK][KNIGHT] |= 1ULL << board.squareIndex('b', 8);
    board.pieces[BLACK][KNIGHT] |= 1ULL << board.squareIndex('g', 8);
    board.pieces[BLACK][QUEEN] |= 1ULL << board.squareIndex('d', 8);
    board.pieces[BLACK][KING] |= 1ULL << board.squareIndex('e', 8);


    // Status
    board.sideToMove =  WHITE;
    board.whiteCanCastleKingside = true;
    board.whiteCanCastleQueenside = true;
    board.blackCanCastleKingside = true;
    board.blackCanCastleQueenside = true;
    board.en_passant_square = -1;
    board.halfmoveclock = 0;
    board.fullmoveNumber = 1;

    board.updateOccupancy();
    return board;
}
