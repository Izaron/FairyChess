#include "evaluator.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

int GetRawCost(TBoardPiece boardPiece) {
    const std::size_t pieceId = boardPiece.GetPieceId();
    return TPieceRegistry::GetPieceInfo(pieceId)->Cost;
}

} // namespace

TEvaluationResult Evaluate(const TBoard& board) {
    TEvaluationResult result;
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.IsEmpty()) {
            continue;
        }
        const int rawCost = GetRawCost(boardPiece);
        (boardPiece.GetColor() == EPieceColor::White ?
            result.WhiteCost : result.BlackCost) += rawCost;
    }
    return result;
}

} // namespace NFairyChess
