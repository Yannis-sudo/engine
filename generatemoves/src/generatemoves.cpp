#include "../include/generatemoves.h"
#include "../include/magic.h"
#include "../../global/include/bitboard.h"

void generateKnightMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard knights = board.pieces[side][KNIGHT];

    while (knights)
    {
        int from = popLSB(knights);
        Bitboard attacks = knightAttacks[from] & ~board.occupied[side];

        // Quiet
        Bitboard quiet = attacks & ~board.occupiedAll;
        while (quiet)
        {
            int to = popLSB(quiet);
            list.add({from, to, KNIGHT, false, false, false, false});
        }

        // Captures
        Bitboard captures = attacks & board.occupied[!side];
        while (captures)
        {
            int to = popLSB(captures);
            list.add({from, to, KNIGHT, true, false, false, false});
        }
    }
}

void generateKingMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard king = board.pieces[side][KING];

    while (king)
    {
        int from = popLSB(king);
        Bitboard attacks = kingAttacks[from] & ~board.occupied[side];

        // Quiet
        Bitboard quiet = attacks & ~board.occupiedAll;
        while (quiet)
        {
            int to = popLSB(quiet);
            list.add({from, to, KING, false, false, false, false});
        }

        // Captures
        Bitboard captures = attacks & board.occupied[!side];
        while (captures)
        {
            int to = popLSB(captures);
            list.add({from, to, KING, true, false, false, false});
        }
    }
}

void generateBishopMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard bishops = board.pieces[side][BISHOP];
    Bitboard occ = board.occupiedAll;

    while (bishops)
    {
        int from = popLSB(bishops);
        Bitboard attacks = getBishopAttacks(from, occ);

        // Quiet moves
        Bitboard quiet = attacks & ~board.occupiedAll;
        while (quiet)
        {
            int to = popLSB(quiet);
            list.add({from, to, BISHOP, false, false, false, false});
        }

        // Captures
        Bitboard captures = attacks & board.occupied[!side];
        while (captures)
        {
            int to = popLSB(captures);
            list.add({from, to, BISHOP, true, false, false, false});
        }
    }
}

void generateRookMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard rooks = board.pieces[side][ROOK];
    Bitboard occ = board.occupiedAll;

    while (rooks)
    {
        int from = popLSB(rooks);
        Bitboard attacks = getRookAttacks(from, occ);

        // Quiet moves
        Bitboard quiet = attacks & ~board.occupiedAll;
        while (quiet)
        {
            int to = popLSB(quiet);
            list.add({from, to, ROOK, false, false, false, false});
        }

        // Captures
        Bitboard captures = attacks & board.occupied[!side];
        while (captures)
        {
            int to = popLSB(captures);
            list.add({from, to, ROOK, true, false, false, false});
        }
    }
}

void generateQueenMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard queens = board.pieces[side][QUEEN];
    Bitboard occ = board.occupiedAll;

    while (queens)
    {
        int from = popLSB(queens);
        Bitboard attacks = getQueenAttacks(from, occ);

        // Quiet Moves
        Bitboard quiet = attacks & ~board.occupiedAll;
        while (quiet)
        {
            int to = popLSB(quiet);
            list.add({from, to, QUEEN, false, false, false, false});
        }

        // Captures
        Bitboard captures = attacks & board.occupied[!side];
        while (captures)
        {
            int to = popLSB(captures);
            list.add({from, to, QUEEN, true, false, false, false});
        }
    }
}

MoveList generateMoves(Board &board)
{
    Board currentBoard;
    MoveList list;
    Color side = board.sideToMove;

    Color oppositeside = side == WHITE  ? BLACK : WHITE;

    generateKnightMoves(board, side, list);
    generateKingMoves(board, side, list);
    generatePawnMoves(board, side, list);

    generateBishopMoves(board, side, list);
    generateRookMoves(board, side, list);
    generateQueenMoves(board, side, list);

    for (int i = 0; i < list.count; i++) {
        const Move &move = list.moves[i];
        Board copy = board;
        makemove(copy, move);

        if (copy.pieces[side][KING] == 0) continue;
        int kingSq = popLSB(copy.pieces[side][KING]);
        if (!isSquareAttacked(kingSq, copy, oppositeside)) {
            list.addLegal(move);
        }

    }
    return list;
}

bool isSquareAttacked(int sq, const Board &board, Color attackingSide) {
    MoveList list;
    generateBishopMoves(board, attackingSide, list);
    generateQueenMoves(board, attackingSide, list);
    generateRookMoves(board, attackingSide, list);
    generateKingMoves(board, attackingSide, list);
    generateKnightMoves(board, attackingSide, list);
    generatePawnMoves(board, attackingSide, list);

    for (int i = 0; i < list.count; i++) {
        if (list.moves[i].to == sq) {
            return true;
        }
    }
    return false;
}