#include "../include/bestmove.h"
#include <limits>
#include <string>
#include <cctype> // für std::tolower

std::string bestmove(Board &board, bool maximizing, int maxDepth)
{
    MoveList rootMoves = generateMoves(board);

    for (int i = 0; i < rootMoves.count2; i++) {
        std::cout << rootMoves.legalMoves[i].from << "-" << rootMoves.legalMoves[i].to << std::endl;
    }

    Move bestMove;
    bestMove.isNull = true;

    int bestEval = maximizing
                       ? std::numeric_limits<int>::min()
                       : std::numeric_limits<int>::max();

    // Iterative Deepening
    for (int depth = 1; depth <= maxDepth; depth++)
    {
        Move currentBest;
        currentBest.isNull = true;

        int currentBestEval = maximizing
                                  ? std::numeric_limits<int>::min()
                                  : std::numeric_limits<int>::max();

        // Suche auf aktueller Tiefe
        for (int i = 0; i < rootMoves.count2; i++)
        {
            Move move = rootMoves.legalMoves[i];

            Board copy = board;
            makemove(copy, move);

            int eval = minimax(copy, depth, -1000000, 1000000);

            if (maximizing)
            {
                if (currentBest.isNull || eval > currentBestEval)
                {
                    currentBestEval = eval;
                    currentBest = move;
                    currentBest.isNull = false;
                }
            }
            else
            {
                if (currentBest.isNull || eval < currentBestEval)
                {
                    currentBestEval = eval;
                    currentBest = move;
                    currentBest.isNull = false;
                }
            }
        }

        // Nach jeder Tiefe aktualisieren wir den global besten Zug
        if (!currentBest.isNull)
        {
            bestMove = currentBest;
            bestEval = currentBestEval;
        }

        // Debug-Ausgabe (optional)
        std::cout << "Depth " << depth
                  << " bestEval=" << bestEval
                  << " move=" << bestMove.from << bestMove.to
                  << std::endl;
    }

    // Falls keine Züge vorhanden sind (Matt/Pat)
    if (bestMove.isNull)
        return "bestmove 0000";

    // UCI-Notation bauen
    char fileChars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    int from_rank = bestMove.from / 8;
    int from_file = bestMove.from % 8;
    int to_rank = bestMove.to / 8;
    int to_file = bestMove.to % 8;

    std::string uciMove;

    uciMove += fileChars[from_file];
    uciMove += std::to_string(from_rank + 1);
    uciMove += fileChars[to_file];
    uciMove += std::to_string(to_rank + 1);

    if (bestMove.promotion)
    {
        char promoChar = "nbrq"[bestMove.promoteTo];
        uciMove += promoChar;
    }

    return "bestmove " + uciMove;
}
