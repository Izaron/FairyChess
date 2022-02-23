#pragma once

#include "board.h"

namespace NFairyChess {

struct TZobristHashing {
    static uint32_t CalculateHash(const TBoard& board, EPieceColor playerColor, int minimaxDepth);
};

} // namespace NFairyChess
