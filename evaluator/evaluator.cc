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

    // calculate cost of pieces
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.IsEmpty()) {
            continue;
        }
        const int rawCost = GetRawCost(boardPiece);
        (boardPiece.GetColor() == EPieceColor::White ?
            result.WhiteCost : result.BlackCost) += rawCost;
    }

    // calculate number of available moves
    result.WhiteAvailableMoves = GenerateMoves(board, EPieceColor::White).MovesCount;
    result.BlackAvailableMoves = GenerateMoves(board, EPieceColor::Black).MovesCount;

    return result;
}

} // namespace NFairyChess
