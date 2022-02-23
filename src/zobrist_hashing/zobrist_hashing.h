#pragma once

#include "board.h"

namespace NFairyChess {

struct TZobristHashing {
    static uint32_t CalculateHash(const TBoard& board, EPieceColor playerColor, int minimaxDepth);
    static uint32_t CalculateSimpleHash(const TBoard& board);
};

} // namespace NFairyChess
