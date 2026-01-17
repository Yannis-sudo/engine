#include "../include/board.h"
#include <iostream>

// Implement methods from board.h
void Board::updateOccupancy()
{
    occupied[WHITE] = 0ULL;
    occupied[BLACK] = 0ULL;

    for (int pt = 0; pt < 6; ++pt)
    {
        occupied[WHITE] |= pieces[WHITE][pt];
        occupied[BLACK] |= pieces[BLACK][pt];
    }

    occupiedAll = occupied[WHITE] | occupied[BLACK];
}

void Board::printBoard() {
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " "; // Reihenbeschriftung
        for (int file = 0; file < 8; ++file) {
            int sq = rank * 8 + file;
            Bitboard mask = 1ULL << sq;
            char symbol = '.';

            for (int c = 0; c < 2; ++c) {
                for (int pt = 0; pt < 6; ++pt) {
                    if (pieces[c][pt] & mask) {
                        symbol = "PNBRQKpnbrqk"[c * 6 + pt];
                    }
                }
            }
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n"; // Spaltenbeschriftung
}

