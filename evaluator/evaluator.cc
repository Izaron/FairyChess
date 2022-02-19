#include "evaluator.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

std::size_t GetRawCost(TBoardPiece boardPiece) {
    const std::size_t pieceId = boardPiece.GetPieceId();
    return TPieceRegistry::GetPieceInfo(pieceId)->Cost;
}

} // namespace

TEvaluationResult Evaluate(const TBoard& board) {
    TEvaluationResult result;
    for (TBoardPiece bp : board) {
        if (bp.IsEmpty()) {
            continue;
        }
        const std::size_t rawCost = GetRawCost(bp);
        (bp.GetColor() == EPieceColor::White ?
            result.WhiteCost : result.BlackCost) += rawCost;
    }
    return result;
}

} // namespace NFairyChess
