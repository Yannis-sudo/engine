#ifndef BITBOARD_H
#define BITBOARD_H

#include "./bitboard.h"
#include "../../tables/include/attacks.h"
#include "../../tables/include/lookup.h"
#include <iostream>

// Data sructs
enum Color
{
    WHITE = 0,
    BLACK = 1
};

enum PieceType
{
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5
};

struct Move {
    int from;
    int to;
    int piece;
    bool captured;
    bool promotion;
    bool en_passant;
    bool castling;
    PieceType promoteTo = PAWN;
    bool isNull = false;
};

enum GameStage
{
    OPENING,
    MIDDLEGAME,
    ENDGAME
};

enum GameResult
{
    GAME_ONGOING = 0,
    WHITE_WINS = 1,
    BLACK_WINS = 2,
    DRAW_STALEMATE = 3,
    DRAW_50_MOVES = 4,
    DRAW_REPETITION = 5,
    DRAW_INSUFFICIENT_MATERIAL = 6
};

constexpr int WHITE_KINGSIDE = 0b0001; // Rechte des weißen Königs zur kurzen Rochade
constexpr int WHITE_QUEENSIDE = 0b0010; // Rechte des weißen Königs zur langen Rochade
constexpr int BLACK_KINGSIDE = 0b0100; // Rechte des schwarzen Königs zur kurzen Rochade
constexpr int BLACK_QUEENSIDE = 0b1000; // Rechte des schwarzen Königs zur langen Rochade


struct HistoryEntry
{
    uint64_t zobristKey;
    int halfmoveClock;
    int castlingRights;
    int enPassantSquare;
    Move move;
    int capturedPiece;
};

struct Board
{
    Bitboard pieces[2][6]; // Color, Type

    // Occupied Squares
    Bitboard occupied[2]; // Black, White
    Bitboard occupiedAll;

    // Game Stage
    Color sideToMove;
    int castlingRights;

    // Castling Rights
    bool wks;
    bool wqs;
    bool bks;
    bool bqs;

    int en_passant_square; // -1 if not possible
    int halfmoveclock;
    int fullmoveNumber;

    uint64_t zobristKey;
    HistoryEntry history[1024];
    int historySize = 0;

    // Methods
    void updateOccupancy();
    void printBoard(); // For debug
    inline int squareIndex(char file, int rank)
    {
        return (rank - 1) * 8 + (file - 'a');
    }
};

// Hilfsfunktionen
bool isSquareAttacked(const Board &board, const Color attackingside, const int sq) noexcept;
void printBitboard(Bitboard bb);

#endif