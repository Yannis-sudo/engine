#ifndef BITBOARD_H
#define BITBOARD_H

#include "./bitboard.h"


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
    GAME_ONGOING,
    WHITE_WINS,
    BLACK_WINS,
    DRAW_STALEMATE,
    DRAW_50_MOVES,
    DRAW_REPETITION,
    DRAW_INSUFFICIENT_MATERIAL
};


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

#endif