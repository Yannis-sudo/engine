#include "../include/generatemovesvar.h"

int bishopRelevantBits[64];
int rookRelevantBits[64];

void initRelevantBits() {
    for (int sq = 0; sq < 64; sq++) {
        bishopRelevantBits[sq] = countBits(bishopMasks[sq]);
        rookRelevantBits[sq]   = countBits(rookMasks[sq]);
    }
}