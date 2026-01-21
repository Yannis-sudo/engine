#include "../include/minimax.h"

const int MATE = 30000;

int negamax(Board &board, int depth, int alpha, int beta) {
    std::cout << "Negamax";

    // 1. Game Over prüfen
    GameResult result = isGameOver(board);

    if (result != GAME_ONGOING) {
        switch (result) {
            case WHITE_WINS:
                return +MATE - depth;
            case BLACK_WINS:
                return -MATE + depth;
            case DRAW_STALEMATE:
            case DRAW_50_MOVES:
            case DRAW_REPETITION:
            case DRAW_INSUFFICIENT_MATERIAL:
                return 0;
            default:
                break;
        }
    }

    // 2. Tiefe erreicht → Eval aus Sicht der Seite am Zug
    if (depth == 0) {
        int eval = evaluate(board);
        return (board.sideToMove == WHITE ? eval : -eval);
    }

    // 3. Züge generieren
    MoveList moves = generateMoves(board);

    int best = -1000000000;

    for (int i = 0; i < moves.count2; i++) {

        Board copy = board;
        makemove(copy, moves.legalMoves[i]);

        // Negamax: Vorzeichen drehen
        int score = -negamax(copy, depth - 1, -beta, -alpha);

        if (score > best)
            best = score;

        if (score > alpha)
            alpha = score;

        if (alpha >= beta)
            break; // Alpha-Beta Cutoff
    }

    return best;
}
