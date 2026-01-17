#include "../include/pawnattacks.h"

void generatePawnMoves(const Board &board, Color side, MoveList &list)
{
    Bitboard pawns = board.pieces[side][PAWN];
    int direction = (side == WHITE) ? 8 : -8;

    while (pawns)
    {
        int from = popLSB(pawns);
        int rank = from / 8;
        int file = from % 8;   // <-- Spalte berechnen (0 = a, 7 = h)

        // Vorwärtszug
        int to = from + direction;
        if (!(to >= 0) || !(to < 64)) {
            continue;
        }

        if (!(board.occupiedAll & (1ULL << to)))
        {
            if ((side == WHITE && rank == 6) || (side == BLACK && rank == 1))
            {
                // Promotion
                list.add({from, to, PAWN, false, true, false, false, QUEEN});
                list.add({from, to, PAWN, false, true, false, false, ROOK});
                list.add({from, to, PAWN, false, true, false, false, BISHOP});
                list.add({from, to, PAWN, false, true, false, false, KNIGHT});
            }
            else
            {
                list.add({from, to, PAWN, false, false, false, false, PAWN});
            }

            // Doppelschritt
            int to2 = from + 2 * direction;
            if (!(board.occupiedAll & (1ULL << to2)))
            {
                if ((side == WHITE && rank == 1) || (side == BLACK && rank == 6))
                    list.add({from, to2, PAWN, false, false, false, false, PAWN});
            }
        }

        // Schlagzüge
        if (side == WHITE) {
            // links schlagen (nur wenn nicht auf Spalte a)
            if (file > 0) {
                int capSq = from + 7;
                if (board.occupied[BLACK] & (1ULL << capSq)) {
                    if (rank == 6) {
                        // Promotion mit Schlag
                        list.add({from, capSq, PAWN, true, true, false, false, QUEEN});
                        list.add({from, capSq, PAWN, true, true, false, false, ROOK});
                        list.add({from, capSq, PAWN, true, true, false, false, BISHOP});
                        list.add({from, capSq, PAWN, true, true, false, false, KNIGHT});
                    } else {
                        list.add({from, capSq, PAWN, true, false, false, false, PAWN});
                    }
                }
            }
            // rechts schlagen (nur wenn nicht auf Spalte h)
            if (file < 7) {
                int capSq = from + 9;
                if (board.occupied[BLACK] & (1ULL << capSq)) {
                    if (rank == 6) {
                        list.add({from, capSq, PAWN, true, true, false, false, QUEEN});
                        list.add({from, capSq, PAWN, true, true, false, false, ROOK});
                        list.add({from, capSq, PAWN, true, true, false, false, BISHOP});
                        list.add({from, capSq, PAWN, true, true, false, false, KNIGHT});
                    } else {
                        list.add({from, capSq, PAWN, true, false, false, false, PAWN});
                    }
                }
            }
        } else { // Schwarz
            // rechts schlagen (nur wenn nicht auf Spalte a)
            if (file > 0) {
                int capSq = from - 9;
                if (board.occupied[WHITE] & (1ULL << capSq)) {
                    if (rank == 1) {
                        list.add({from, capSq, PAWN, true, true, false, false, QUEEN});
                        list.add({from, capSq, PAWN, true, true, false, false, ROOK});
                        list.add({from, capSq, PAWN, true, true, false, false, BISHOP});
                        list.add({from, capSq, PAWN, true, true, false, false, KNIGHT});
                    } else {
                        list.add({from, capSq, PAWN, true, false, false, false, PAWN});
                    }
                }
            }
            // links schlagen (nur wenn nicht auf Spalte h)
            if (file < 7) {
                int capSq = from - 7;
                if (board.occupied[WHITE] & (1ULL << capSq)) {
                    if (rank == 1) {
                        list.add({from, capSq, PAWN, true, true, false, false, QUEEN});
                        list.add({from, capSq, PAWN, true, true, false, false, ROOK});
                        list.add({from, capSq, PAWN, true, true, false, false, BISHOP});
                        list.add({from, capSq, PAWN, true, true, false, false, KNIGHT});
                    } else {
                        list.add({from, capSq, PAWN, true, false, false, false, PAWN});
                    }
                }
            }
        }

        // En Passant
        if (board.en_passant_square == -1) continue;
        if (side == WHITE) {
            if (file > 0)
            {
                int capSq = from + 7;
                if (capSq == board.en_passant_square)
                {
                    list.add({from, capSq, PAWN, true, false, true, false, PAWN});
                }
            }
            if (file < 7) {
                int capSq = from + 9;
                if (capSq == board.en_passant_square) {
                    list.add({from, capSq, PAWN, true, false, true, false, PAWN});
                }
            }
        } else {
            if (file > 0) {
                int capSq = from - 9;
                if (capSq == board.en_passant_square) {
                    list.add({from, capSq, PAWN, true, false, true, false, PAWN});
                }
            }
            if (file < 7) {
                int capSq = from - 7;
                if (capSq == board.en_passant_square) {
                    list.add({from, capSq, PAWN, true, false, true, false, PAWN});
                }
            }
        }
    }
}
