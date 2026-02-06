#include "../include/attacks.h"

// Global Arrays (definded in ../include/attacks.h)
Bitboard knightAttacks[64];
Bitboard kingAttacks[64];

Bitboard bishopAttacks[64][1024];
Bitboard rookAttacks[64][4096];

Bitboard pawnAttacksWhite[64];
Bitboard pawnAttacksBlack[64];

void initAttackTable() // Init the attack table for the knights and the king
{
    // Knight
    for (int sq = 0; sq < 64; ++sq)
    {
        int rank = sq / 8;
        int file = sq % 8;

        knightAttacks[sq] = 0ULL;
        int knightMoves[8][2] = {
            {+2, +1},
            {+2, -1},
            {-2, +1},
            {-2, -1},
            {+1, +2},
            {+1, -2},
            {-1, +2},
            {-1, -2}};

        for (auto &m : knightMoves)
        {
            int r = rank + m[0];
            int f = file + m[1];
            if (onBoard2d(r, f))
            {
                knightAttacks[sq] |= 1ULL << (r * 8 + f);
            }
        }
    }

    // King
    for (int sq = 0; sq < 64; ++sq)
    {
        int rank = sq / 8;
        int file = sq % 8;

        kingAttacks[sq] = 0ULL;
        int kingMoves[8][2] = {
            {+1, 0},
            {-1, 0},
            {0, +1},
            {0, -1},
            {+1, +1},
            {+1, -1},
            {-1, +1},
            {-1, -1}};
        for (auto &m : kingMoves)
        {
            int r = rank + m[0];
            int f = file + m[1];
            if (onBoard2d(r, f))
            {
                kingAttacks[sq] |= 1ULL << (r * 8 + f);
            }
        }
    }
}

Bitboard maskOccupancy(int index, Bitboard mask)
{
    Bitboard occ = 0ULL;
    int bits = countBits(mask);

    Bitboard temp = mask; // <<< WICHTIG: Kopie erzeugen

    for (int i = 0; i < bits; i++)
    {
        int sq = popLSB(temp); // <<< NICHT mask verändern!
        if (index & (1 << i))
            occ |= 1ULL << sq;
    }
    return occ;
}

void initBishopRookTables()
{
    for (int sq = 0; sq < 64; ++sq)
    {
        // ================= BISHOP =================
        Bitboard mask = bishopMasks[sq];
        int bits = bishopRelevantBits[sq];
        int variations = 1 << bits;

        for (int i = 0; i < variations; ++i)
        {
            Bitboard occ = maskOccupancy(i, bishopMasks[sq]);

            int index = (occ * bishopMagics[sq]) >> (64 - bits);
            bishopAttacks[sq][index] = computeBishopTable(sq, occ);
        }

        // ================= ROOK =================
        mask = rookMasks[sq];
        int bits2 = countBits(mask);
        int variations2 = 1 << bits2;

        for (int i = 0; i < variations2; ++i)
        {
            Bitboard occ = maskOccupancy(i, mask);
            Bitboard occMasked = occ & mask; // <<< WICHTIG

            int index = (occMasked * rookMagics[sq]) >>
                        (64 - rookRelevantBits[sq]);

            rookAttacks[sq][index] = computeRookTable(sq, occMasked);
        }
    }
}

// Compute Tables (used in initBishopRookTables() in this file)
Bitboard computeBishopTable(int sq, Bitboard occ)
{
    Bitboard attacks = 0ULL;
    int rank = sq / 8;
    int file = sq % 8;

    for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; ++r, ++f)
    {
        int target = r * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; ++r, --f)
    {
        int target = r * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; --r, ++f)
    {
        int target = r * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f)
    {
        int target = r * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }

    return attacks;
}
Bitboard computeRookTable(int sq, Bitboard occ)
{
    Bitboard attacks = 0ULL;
    int rank = sq / 8;
    int file = sq % 8;

    for (int r = rank + 1; r <= 7; ++r)
    {
        int target = r * 8 + file;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int r = rank - 1; r >= 0; --r)
    {
        int target = r * 8 + file;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int f = file + 1; f <= 7; ++f)
    {
        int target = rank * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    for (int f = file - 1; f >= 0; --f)
    {
        int target = rank * 8 + f;
        attacks |= 1ULL << target;
        if (occ & (1ULL << target))
            break;
    }
    return attacks;
}

void initPawnAttacks() // Init the pawn attacks tables
{
    for (int sq = 0; sq < 64; ++sq)
    {
        pawnAttacksWhite[sq] = 0ULL;
        pawnAttacksBlack[sq] = 0ULL;

        int rank = sq / 8;
        int file = sq % 8;

        // White
        if (file > 0 && rank < 7)
        {
            pawnAttacksWhite[sq] |= 1ULL << (sq + 7);
        }
        if (file < 7 && rank < 7)
        {
            pawnAttacksWhite[sq] |= 1ULL << (sq + 9);
        }

        // Black
        if (file > 0 && rank > 0)
        {
            pawnAttacksBlack[sq] |= 1ULL << (sq - 9);
        }
        if (file < 7 && rank > 0)
        {
            pawnAttacksBlack[sq] |= 1ULL << (sq - 7);
        }
    }
}
