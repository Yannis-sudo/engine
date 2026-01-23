#include "../include/qsearch.h"

int quiescence(int alpha, int beta, Board &board) {
    int standPat = evaluate(board);

    if (standPat >= beta) {
        return beta;
    }
    if (standPat > alpha) {
        alpha = standPat;
    }

    // Generate only captures
    MoveList captures = generateCaptures(board);
    const Color side = board.sideToMove;
    const Color opp = (Color)(board.sideToMove ^ 1);

    // Loop trough all capture moves
    for (int i = 0; i < captures.count; i++) {
        const Move m = captures.moves[i];

        makemove(board, m);

        Bitboard kingBB = board.pieces[side][KING];
        int kingSQ = popLSB(kingBB);

        if (!isSquareAttacked(board, opp, kingSQ)) {
            int score = -quiescence(alpha, beta, board);
            if (score >= beta) {
                undomove(board);
                return beta;
            }
            if (score > alpha) {
                alpha = score;
            }
        }
        undomove(board);
    }
    return alpha;
}