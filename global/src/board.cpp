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

void Board::printBoard()
{
    for (int rank = 7; rank >= 0; --rank)
    {
        std::cout << rank + 1 << " "; // Reihenbeschriftung
        for (int file = 0; file < 8; ++file)
        {
            int sq = rank * 8 + file;
            Bitboard mask = 1ULL << sq;
            char symbol = '.';

            for (int c = 0; c < 2; ++c)
            {
                for (int pt = 0; pt < 6; ++pt)
                {
                    if (pieces[c][pt] & mask)
                    {
                        symbol = "PNBRQKpnbrqk"[c * 6 + pt];
                    }
                }
            }
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n"; // Spaltenbeschriftung
    if (sideToMove == WHITE)
    {
        std::cout << "Side to move: White" << std::endl;
    }
    else
    {
        std::cout << "Side to move: Black" << std::endl;
    }

    std::cout << "Castling Rights: K:" << wks << " Q:" << wqs << " k:" << bks << " q:" << bqs << std::endl;
    std::cout << "En Passant: " << en_passant_square << " Half Move Clock: " << halfmoveclock << std::endl;
}

bool isSquareAttacked(const Board &board, const Color attackingside, const int sq) noexcept
{
    // pawn
    if (sq < 0 || sq >= 64)
    {
        std::cerr << "INVALID sq: " << sq << std::endl;
        return false;
    }

    if (attackingside == WHITE)
    {
        if (pawnAttacksBlack[sq] & board.pieces[WHITE][PAWN])
        {
            return true; // White pawn
        }
    }
    else
    {
        if (pawnAttacksWhite[sq] & board.pieces[BLACK][PAWN])
        {
            return true; // black pawn
        }
    }

    // knight
    if (knightAttacks[sq] & board.pieces[attackingside][KNIGHT])
    {
        return true;
    }
    // king
    if (kingAttacks[sq] & board.pieces[attackingside][KING])
    {
        return true;
    }

    // bishop / queen
    if (getBishopAttacks(sq, board.occupiedAll) & (board.pieces[attackingside][BISHOP] | board.pieces[attackingside][QUEEN]))
    {
        return true;
    }

    // rook / queen
    if (getRookAttacks(sq, board.occupiedAll) & (board.pieces[attackingside][ROOK] | board.pieces[attackingside][QUEEN]))
    {
        return true;
    }

    return false;
}

void printBitboard(Bitboard bb)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file < 8; file++)
        {
            int sq = rank * 8 + file;
            std::cout << (((bb >> sq) & 1ULL) ? "1 " : ". ");
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
