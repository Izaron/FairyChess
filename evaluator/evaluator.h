#pragma once

#include "board.h"

namespace NFairyChess {

struct TEvaluationResult {
    std::size_t WhiteCost = 0;
    std::size_t BlackCost = 0;
};

TEvaluationResult Evaluate(const TBoard& board);

} // namespace NFairyChess
