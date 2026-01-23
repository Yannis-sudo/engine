#pragma once
#include "../../global/include/board.h"
#include "../../global/include/movelist.h"

inline void reorderMovesFirst(MoveList &list, const Move bestMove)
{
    // If no best move is stored, do nothing
    if (bestMove.from == -1)
        return;

    for (int i = 0; i < list.count2; i++)
    {
        if (list.legalMoves[i].from == bestMove.from &&
            list.legalMoves[i].to == bestMove.to &&
            list.legalMoves[i].piece == bestMove.piece &&
            list.legalMoves[i].promotion == bestMove.promotion &&
            list.legalMoves[i].promoteTo == bestMove.promoteTo) {
                Move temp = list.legalMoves[0];
                list.legalMoves[0] = list.legalMoves[i];
                list.legalMoves[i] = temp;
                return;
            }
    }
}