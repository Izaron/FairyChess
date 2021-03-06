#include "evaluator.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

int GetPieceCost(TBoardPiece boardPiece) {
    const std::size_t pieceId = boardPiece.GetPieceId();
    return TPieceRegistry::GetPieceInfo(pieceId)->Cost;
}

} // namespace

TEvaluationResult Evaluate(const TBoard& board, bool calculateAvailableMoves) {
    TEvaluationResult result;

    // calculate cost of pieces
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.IsEmpty()) {
            continue;
        }
        const int cost = GetPieceCost(boardPiece);
        (boardPiece.GetColor() == EPieceColor::White ?
            result.WhiteCost : result.BlackCost) += cost;
    }

    // calculate number of available moves
    if (calculateAvailableMoves) {
        {
            TDummyMoveContainer moveContainer;
            GenerateMoves(moveContainer, board, EPieceColor::White);
            result.WhiteAvailableMoves = moveContainer.MovesCount;
        }
        {
            TDummyMoveContainer moveContainer;
            GenerateMoves(moveContainer, board, EPieceColor::Black);
            result.BlackAvailableMoves = moveContainer.MovesCount;
        }
    }

    return result;
}

TEvaluationResult EvaluateDelta(const TBoard& board, const TMove& move) {
    TEvaluationResult result;
    for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
        const TBoardUpdate& update = move.Updates[i];

        // substract the old piece cost
        TBoardPiece oldBoardPiece = board.GetBoardPiece(update.Position);
        if (!oldBoardPiece.IsEmpty()) {
            const int cost = GetPieceCost(oldBoardPiece);
            (oldBoardPiece.GetColor() == EPieceColor::White ?
                result.WhiteCost : result.BlackCost) -= cost;
        }

        // add the new piece cost
        TBoardPiece newBoardPiece = update.NewBoardPiece;
        if (!newBoardPiece.IsEmpty()) {
            const int cost = GetPieceCost(newBoardPiece);
            (newBoardPiece.GetColor() == EPieceColor::White ?
                result.WhiteCost : result.BlackCost) += cost;
        }
    }
    return result;
}

} // namespace NFairyChess
