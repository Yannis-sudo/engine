#include "../include/bestmove.h"
#include <limits>
#include <string>
#include <cctype> // für std::tolower

std::string bestmove(Board &board, bool maximizing, int depth)
{
    MoveList possibleMoves = generateMoves(board);

    Move bestMove;
    bestMove.isNull = true;

    int bestEval = maximizing
        ? std::numeric_limits<int>::min()
        : std::numeric_limits<int>::max();

    // Beste Variante per Minimax suchen
    for (int i = 0; i < possibleMoves.count2; i++)
    {
        Move move = possibleMoves.legalMoves[i];

        Board copy = board;
        makemove(copy, move);
        int eval = negamax(
            copy,
            depth,
            -1000000,
            1000000
        );
        if (maximizing)
        {
            if (bestMove.isNull || eval > bestEval)
            {
                bestEval = eval;
                bestMove = move;
                bestMove.isNull = false;
            }
        }
        else
        {
            if (bestMove.isNull || eval < bestEval)
            {
                bestEval = eval;
                bestMove = move;
                bestMove.isNull = false;
            }
        }
    }

    // Falls keine Züge vorhanden sind (Matt/Pat)
    if (bestMove.isNull)
    {
        return "bestmove 0000"; // UCI-„Nullzug“
    }

    // UCI-Notation bauen: e2e4, e7e8q etc.
    char fileChars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char pieceTypesW[6] = {'P', 'N', 'B', 'R', 'Q', 'K'};
    char pieceTypesB[6] = {'p', 'n', 'b', 'r', 'q', 'k'};

    int from_rank = bestMove.from / 8;
    int from_file = bestMove.from % 8;
    int to_rank   = bestMove.to   / 8;
    int to_file   = bestMove.to   % 8;

    std::string uciMove;

    // from
    uciMove += fileChars[from_file];
    uciMove += std::to_string(from_rank + 1); // +1 weil UCI 1–8 benutzt

    // to
    uciMove += fileChars[to_file];
    uciMove += std::to_string(to_rank + 1);

    // Promotion (z.B. e7e8q)
    if (bestMove.promotion)
    {
        char promoChar;
        if (maximizing)
            promoChar = pieceTypesW[bestMove.promoteTo];
        else
            promoChar = pieceTypesB[bestMove.promoteTo];

        // UCI will den Promotyp klein (q, r, b, n)
        uciMove += static_cast<char>(std::tolower(static_cast<unsigned char>(promoChar)));
    }

    return uciMove;
}
