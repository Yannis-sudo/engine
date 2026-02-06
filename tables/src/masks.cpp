#include "../include/masks.h"

Bitboard bishopMasks[64];
Bitboard rookMasks[64];

void initMasks()
{
    for (int sq = 0; sq < 64; ++sq)
    {
        int rank = sq / 8;
        int file = sq % 8;

        Bitboard mask = 0ULL;

        for (int r = rank + 1, f = file + 1; r < 7 && f < 7; r++, f++)
            mask |= 1ULL << (r * 8 + f);

        for (int r = rank + 1, f = file - 1; r < 7 && f > 0; r++, f--)
            mask |= 1ULL << (r * 8 + f);

        for (int r = rank - 1, f = file + 1; r > 0 && f < 7; r--, f++)
            mask |= 1ULL << (r * 8 + f);

        for (int r = rank - 1, f = file - 1; r > 0 && f > 0; r--, f--)
            mask |= 1ULL << (r * 8 + f);

        bishopMasks[sq] = mask;

        mask = 0ULL;
        for (int r = rank + 1; r < 7; ++r)
        {
            mask |= 1ULL << (r * 8 + file);
        }
        for (int r = rank - 1; r > 0; --r)
        {
            mask |= 1ULL << (r * 8 + file);
        }
        for (int f = file + 1; f < 7; ++f)
        {
            mask |= 1ULL << (rank * 8 + f);
        }
        for (int f = file - 1; f > 0; --f)
        {
            mask |= 1ULL << (rank * 8 + f);
        }
        rookMasks[sq] = mask;
    }
}