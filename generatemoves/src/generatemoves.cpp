#include "../include/generatemoves.h"
#include "../include/magic.h"
#include "../../global/include/bitboard.h"

void generateKnightMoves(const Board &board, Color side, MoveList &list) noexcept
{
    Bitboard knights = board.pieces[side][KNIGHT];

    while (knights)
    {
        int from = popLSB(knights);
        Bitboard attacks = knightAttacks[from] & ~board.occupied[side];

        while (attacks)
        {
            int to = popLSB(attacks);
            bool isCapture = (board.occupied[!side] & (1ULL << to)) != 0;
            list.add({from, to, KNIGHT, isCapture, false, false, false});
        }
    }
}

void generateKingMoves(const Board &board, Color side, MoveList &list) noexcept
{
    Bitboard king = board.pieces[side][KING];

    while (king)
    {
        int from = popLSB(king);
        Bitboard attacks = kingAttacks[from] & ~board.occupied[side];

        while (attacks)
        {
            int to = popLSB(attacks);
            bool isCapture = (board.occupied[!side] & (1ULL << to)) != 0;
            list.add({from, to, KING, isCapture, false, false, false});
        }

        // Castling
        addCastlingMoves(board, list);
    }
}

void generateBishopMoves(const Board &board, Color side, MoveList &list) noexcept
{
    Bitboard bishops = board.pieces[side][BISHOP];
    Bitboard occ = board.occupiedAll;

    while (bishops)
    {
        int from = popLSB(bishops);
        Bitboard attacks = getBishopAttacks(from, occ);

        while (attacks)
        {
            int to = popLSB(attacks);
            bool isCapture = (board.occupied[!side] & (1ULL << to)) != 0;
            list.add({from, to, BISHOP, isCapture, false, false, false});
        }
    }
}

void generateRookMoves(const Board &board, Color side, MoveList &list) noexcept
{
    Bitboard rooks = board.pieces[side][ROOK];
    Bitboard occ = board.occupiedAll;

    while (rooks)
    {
        int from = popLSB(rooks);
        Bitboard attacks = getRookAttacks(from, occ); // Lookup rook attacks

        // Quiet moves
        while (attacks)
        {
            int to = popLSB(attacks);
            bool isCapture = (board.occupied[!side] & (1ULL << to)) != 0;
            list.add({from, to, ROOK, isCapture, false, false, false});
        }
    }
}

void generateQueenMoves(const Board &board, Color side, MoveList &list) noexcept
{
    Bitboard queens = board.pieces[side][QUEEN];
    Bitboard occ = board.occupiedAll;

    while (queens)
    {
        int from = popLSB(queens);
        Bitboard attacks = getQueenAttacks(from, occ);

        while (attacks)
        {
            int to = popLSB(attacks);
            bool isCapture = (board.occupied[!side] & (1ULL << to)) != 0;
            list.add({from, to, QUEEN, isCapture, false, false, false});
        }
    }
}

MoveList generateMoves(Board &board)
{
    MoveList list;

    // local side variables
    const Color side = board.sideToMove;
    const Color opp = (Color)(side ^ 1);

// Thread
#pragma omp parallel sections
    {
#pragma omp section
        generateKnightMoves(board, side, list);

#pragma omp section
        generateKingMoves(board, side, list);

#pragma omp section
        generatePawnMoves(board, side, list);

#pragma omp section
        generateBishopMoves(board, side, list);

#pragma omp section
        generateRookMoves(board, side, list);

#pragma omp section
        generateQueenMoves(board, side, list);
    }

    for (int i = 0; i < list.count; i++)
    {
        const Move &move = list.moves[i];
        makemove(board, move);

        if (board.pieces[side][KING] == 0)
            continue;
        const int kingSq = popLSB(board.pieces[!side][KING]);
        if (!isSquareAttacked(board, opp, kingSq))
        {
            list.addLegal(move);
        }
        undomove(board);
    }
    return list;
}