#include "../include/minimax.h"

int minimax(Board &board, const int depht, int alpha, int beta)
{
    const uint64_t key = board.zobristKey;
    TTEntry &entry = TT[key & (TT_SIZE - 1)];

    const int originalAlpha = alpha;

    // TT
    if (entry.key == key && entry.depth >= depht)
    {
        if (entry.flag == TT_EXACT)
        {
            return entry.score;
        }
        if (entry.flag == TT_ALPHA && entry.score <= alpha)
        {
            return entry.score;
        }
        if (entry.flag == TT_BETA && entry.score >= beta)
        {
            return entry.score;
        }
    }

    // Depht == 0 -> Q-Search
    if (depht == 0)
    {
        return quiescence(board, alpha, beta);
    }

    // Game over check
    GameResult result = isGameOver(board);
    if (result != GAME_ONGOING)
    {
        if (result == WHITE_WINS)
            return 1000000;
        if (result == BLACK_WINS)
            return -1000000;
        return 0;
    }

    // Generate Moves
    MoveList moves = generateMoves(board);
    if (moves.count == 0)
    {
        return 0; // Stalemate or Error
    }

    // Move Order
    if (entry.key == key && entry.bestMove.from != -1)
    {
        reorderMovesFirst(moves, entry.bestMove);
    }

    int bestScore = -10000000;
    Move bestMove = Move(); // default: NO_MOVE

    for (int i = 0; i < moves.count2; i++)
    {
        Move m = moves.legalMoves[i];

        makemove(board, m);

        int score = -minimax(board, depht - 1, -beta, -alpha);

        undomove(board);

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = m;
        }

        if (score > alpha)
        {
            alpha = score;
            if (alpha >= beta)
            {
                break;
            }
        }
    }

    // Store in TT
    entry.key = key;
    entry.score = bestScore;
    entry.depth = depht;
    entry.bestMove = bestMove;

    if (bestScore <= originalAlpha)
        entry.flag = TT_ALPHA;
    else if (bestScore >= beta)
        entry.flag = TT_BETA;
    else
        entry.flag = TT_EXACT;
    return bestScore;
}