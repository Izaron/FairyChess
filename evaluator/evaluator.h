#pragma once

#include "board.h"

namespace NFairyChess {

struct TEvaluationResult {
    int WhiteCost = 0;
    int BlackCost = 0;
};

TEvaluationResult Evaluate(const TBoard& board);

} // namespace NFairyChess
