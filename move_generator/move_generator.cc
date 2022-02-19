#include "move_generator.h"
#include "piece_registry.h"

namespace NFairyChess {

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor) {
    TMoveContainer moveContainer;
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.GetColor() != piecesColor) {
            continue;
        }
        const TPieceInfo* pieceInfo = TPieceRegistry::GetPieceInfo(boardPiece.GetPieceId());
        TMoveContext ctx{
            .MoveContainer = moveContainer,
            .Board = board,
            .Color = piecesColor,
            .Position = iter.Position,
        };
        pieceInfo->FillMovesFn(boardPiece, std::move(ctx));
    }
    return moveContainer;
}

} // namespace NFairyChess
