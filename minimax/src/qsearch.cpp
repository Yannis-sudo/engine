#include "../include/qsearch.h"

int quiescence(Board &board, int alpha, int beta)
{
    int standPat = evaluate(board);

    if (standPat >= beta)
        return beta;

    if (standPat > alpha)
        alpha = standPat;

    MoveList captures = generateCaptures(board);

    for (int i = 0; i < captures.count; i++)
    {
        Move m = captures.moves[i];

        makemove(board, m);

        // side that made the move
        Color us = (Color)(board.sideToMove ^ 1);
        Color them = board.sideToMove;

        // find king square without modifying bitboard
        Bitboard kingBB = board.pieces[us][KING];

        if (kingBB == 0) {
            std::cout << "KING BITBOARD == 0" << std::endl;
        }

        int kingSq = bitScanForward(kingBB);

        if (!isSquareAttacked(board, them, kingSq))
        {
            int score = -quiescence(board, -beta, -alpha);

            if (score >= beta)
            {
                undomove(board);
                return beta;
            }

            if (score > alpha)
                alpha = score;
        }

        undomove(board);
    }

    return alpha;
}
