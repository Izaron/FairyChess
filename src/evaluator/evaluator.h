#pragma once

#include "board.h"
#include "move_generator.h"

namespace NFairyChess {

struct TEvaluationResult {
    int WhiteCost = 0;
    int BlackCost = 0;

    int WhiteAvailableMoves = 0;
    int BlackAvailableMoves = 0;
};

int GetPieceCost(TBoardPiece boardPiece);
TEvaluationResult Evaluate(const TBoard& board, bool calculateAvailableMoves = true);
TEvaluationResult EvaluateDelta(const TBoard& board, const TMove& move);

} // namespace NFairyChess
