#include "../include/minimax.h"

int minimax(Board board, const int depht, int alpha, int beta, const bool maximizing)
{
    const uint64_t key = board.hash; //

    if (depht == 0)
    {
        return evaluate(board);
    }
    const GameResult result = isGameOver(board);
    if (result != GAME_ONGOING)
    {
        if (result == DRAW_50_MOVES || DRAW_INSUFFICIENT_MATERIAL || DRAW_REPETITION || DRAW_STALEMATE)
        {
            return 0;
        }
        else if (result == WHITE_WINS)
        {
            return 1000000;
        }
        else if (result == BLACK_WINS)
        {
            return -1000000;
        }
    }

    MoveList moves = generateMoves(board);
    if (maximizing) {
        int best = -10000000;
        for (int i = 0; i < moves.count2; ++i) {
            makemove(board, moves.legalMoves[i]);
            int score = minimax(board, depht - 1, alpha, beta, false);
            undomove(board);

            if (score > best) {
                best = score;
            }
            if (best > alpha) {
                alpha = best;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return best;
    } else {
        int best = 10000000;
        for (int i = 0; i < moves.count2; ++i) {
            makemove(board, moves.legalMoves[i]);
            int score = minimax(board, depht - 1, alpha, beta, true);
            undomove(board);
            if (score < best) {
                best = score;
            }
            if (best < beta) {
                beta = best;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return best;
    }
}