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

        // inverse position for black pieces
        TBoardPosition position = iter.Position;
        if (boardPiece.GetColor() == EPieceColor::Black) {
            position = board.InversePosition(position);
        }

        const TPieceInfo* pieceInfo = TPieceRegistry::GetPieceInfo(boardPiece.GetPieceId());
        TMoveContext ctx{
            .Moves = moveContainer,
            .Board = board,
            .Color = piecesColor,
            .Position = position,
        };
        pieceInfo->FillMovesFn(boardPiece, std::move(ctx));
    }
    return moveContainer;
}

TBoard ApplyMove(const TBoard& board, const TMove& move) {
    TBoard newBoard = board;
    for (const TBoardUpdate& upd : move.Updates) {
        newBoard.SetBoardPiece(upd.Position, upd.NewBoardPiece);
    }
    return newBoard;
}

} // namespace NFairyChess
