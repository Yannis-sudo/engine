#include "../include/positioneval.h"

int MgPST[6][2][64];
int EgPST[6][2][64];

int position_eval_mg(const Board &board)
{
    int score = 0;

    for (int i = 0; i < 6; ++i)
    {
        // White
        Bitboard bb = board.pieces[WHITE][i];
        while (bb)
        {
            const int sq = popLSB(bb);
            score += MgPST[i][WHITE][sq];
        }

        // Black
        Bitboard bb_black = board.pieces[BLACK][i];
        while (bb_black)
        {
            const int sq = popLSB(bb_black);
            score -= MgPST[i][BLACK][sq];
        }
    }

    return score;
}

int position_eval_eg(const Board &board)
{
    int score = 0;

    for (int i = 0; i < 6; ++i)
    {
        // White
        Bitboard bb = board.pieces[WHITE][i];
        while (bb)
        {
            const int sq = popLSB(bb);
            score += EgPST[i][WHITE][sq];
        }

        // Black
        Bitboard bb_black = board.pieces[BLACK][i];
        while (bb_black)
        {
            const int sq = popLSB(bb_black);
            score -= EgPST[i][BLACK][sq];
        }
    }

    return score;
}