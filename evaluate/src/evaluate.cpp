#include "../include/evaluate.h"

int evaluateMG(const Board &board)
{
    // Material eval
    int score = 0;
    for (int p = 0; p <= KING; ++p)
    {
        score += pieceValueMg[p] * countBits(board.pieces[WHITE][p]);
        score -= pieceValueMg[p] * countBits(board.pieces[BLACK][p]);
    }

    // position eval
    score += position_eval_mg(board);

    return score;
}
int evaluateEG(const Board &board)
{
    // Material eval
    int score = 0;
    for (int p = 0; p <= KING; ++p) {
        score += pieceValueEg[p] * countBits(board.pieces[WHITE][p]);
        score -= pieceValueEg[p] * countBits(board.pieces[BLACK][p]);
    }

    // position eval
    score += position_eval_eg(board);
    return score;
}

int evaluate(const Board &board)
{
    int phase = gamestage(board);

    int mg = evaluateMG(board);
    int eg = evaluateEG(board);

    int score = (mg * phase + eg * (24 - phase)) / 24;
    return (board.sideToMove == WHITE ? score : -score);
}