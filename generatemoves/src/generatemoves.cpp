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

// --- Ersetze die parallele Sektion durch sequentielle Aufrufe ---
MoveList generateMoves(Board &board)
{
    MoveList list;

    const Color side = board.sideToMove;
    const Color opp  = (side == WHITE ? BLACK : WHITE);

    // Generate pseudo-legal moves for the side to move
    generateKnightMoves(board, side, list);
    generateKingMoves(board, side, list);
    generatePawnMoves(board, side, list);
    generateBishopMoves(board, side, list);
    generateRookMoves(board, side, list);
    generateQueenMoves(board, side, list);

    // Filter to legal moves
    for (int i = 0; i < list.count; i++)
    {
        const Move move = list.moves[i];

        makemove(board, move);

        // side is the side that made the move
        Bitboard kingBB = board.pieces[side][KING];

        // if king disappeared, illegal move
        if (kingBB == 0)
        {
            undomove(board);
            continue;
        }

        // find king square without modifying bitboard
        int kingSq = bitScanForward(kingBB);

        // check if our king is in check after the move
        if (!isSquareAttacked(board, opp, kingSq))
        {
            list.addLegal(move);
        }

        undomove(board);
    }

    return list;
}


MoveList generateCaptures(Board &board) {
    MoveList list;
    const Color side = board.sideToMove;
    const Color opp = (Color)(side ^ 1);

    // PAWN WHITE / BLACK
    Bitboard pawns = board.pieces[side][PAWN];
    while (pawns) {
        const int from = popLSB(pawns);
        if (side == WHITE) {
            Bitboard attacks = pawnAttacksWhite[from] & board.occupied[BLACK];
            while (attacks) {
                const int to = popLSB(attacks);
                list.add({from, to, PAWN, true, false, false, false});
            }
        } else {
            Bitboard attacks = pawnAttacksBlack[from] & board.occupied[WHITE];
            while (attacks) {
                const int to = popLSB(attacks);
                list.add({from , to, PAWN, true, false, false, false});
            }
        }
    }

    // KNIGHT
    Bitboard knights = board.pieces[side][KNIGHT];
    while (knights) {
        int from = popLSB(knights);
        Bitboard attacks = knightAttacks[from] & board.occupied[opp];
        while (attacks) {
            int to = popLSB(attacks);
            list.add({from , to, KNIGHT, true, false, false, false});
        }
    }

    // KING
    Bitboard king = board.pieces[side][KING];
    while (king) {
        int from = popLSB(king);
        Bitboard attacks = kingAttacks[from] & board.occupied[opp];
        while (attacks) {
            int to = popLSB(attacks);
            list.add({from, to, KING, true, false, false, false});
        }
    }

    // BISHOP
    Bitboard bishops = board.pieces[side][BISHOP];
    Bitboard occ = board.occupiedAll;
    while (bishops) {
        int from = popLSB(bishops);
        Bitboard attacks = getBishopAttacks(from, occ) & board.occupied[opp];
        while (attacks) {
            int to = popLSB(attacks);
            list.add({from, to, BISHOP, true, false, false, false});
        }
    }
    // ROOK
    Bitboard rooks = board.pieces[side][ROOK];
    while (rooks) {
        int from = popLSB(rooks);
        Bitboard attacks = getRookAttacks(from, occ) & board.occupied[opp];
        while (attacks) {
            int to = popLSB(attacks);
            list.add({from, to, ROOK, true, false, false, false});
        }
    }

    // QUEEN
    Bitboard queens = board.pieces[side][QUEEN];
    while (queens) {
        int from = popLSB(queens);
        Bitboard attacks = (getBishopAttacks(from , occ) | getRookAttacks(from, occ)) & board.occupied[opp];
        while (attacks) {
            int to = popLSB(attacks);
            list.add({from, to, QUEEN, true, false, false, false});
        } 
    }

    return list;
}