#include "../include/zobrist.h"
#include <random>

uint64_t zobristPiece[2][6][64];
uint64_t zobristSide;
uint64_t zobristCastling[16];
uint64_t zobristEnPassant[64];

void initZobrist()
{
    std::mt19937_64 rng(0xAABBCCDDEEFF1122ULL);

    // Pieces
    for (int c = 0; c < 2; c++)
    {
        for (int p = 0; p < 6; p++)
        {
            for (int sq = 0; sq < 64; sq++)
            {
                zobristPiece[c][p][sq] = rng();
            }
        }
    }
    zobristSide = rng();

    // Castling Rights (0-15)
    for (int i = 0; i < 16; i++) {
        zobristCastling[i] = rng();
    }

    // En Passant
    for (int i = 0; i < 64; i++) {
        zobristEnPassant[i] = rng();
    }
}

uint64_t computeZobrist(const Board &b)
{
    uint64_t h = 0;

    for (int c = 0; c < 2; c++)
        for (int p = 0; p < 6; p++) {
            Bitboard bb = b.pieces[c][p];
            while (bb) {
                int sq = popLSB(bb);
                h ^= zobristPiece[c][p][sq];
            }
        }

    if (b.sideToMove == BLACK)
        h ^= zobristSide;

    h ^= zobristCastling[b.castlingRights];

    if (b.en_passant_square != -1)
        h ^= zobristEnPassant[b.en_passant_square];

    return h;
}
