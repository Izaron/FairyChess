#include "move_generator.h"
#include "piece_registry.h"

namespace NFairyChess {

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor) {
    const bool isInverted = piecesColor == EPieceColor::Black;
    TMoveContainer moveContainer;
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.GetColor() != piecesColor) {
            continue;
        }

        // inverse position for black pieces
        TBoardPosition position = iter.Position;
        if (isInverted) {
            position = board.InversePosition(position);
        }

        const TPieceInfo* pieceInfo = TPieceRegistry::GetPieceInfo(boardPiece.GetPieceId());
        TMoveContext ctx{
            .Moves = moveContainer,
            .Board = TOrientedBoard{board, isInverted},
            .Position = position,
        };
        pieceInfo->FillMovesFn(boardPiece, std::move(ctx));
    }

    // inverse back position for black pieces
    if (isInverted) {
        for (auto& move : moveContainer) {
            for (auto& upd : move.Updates) {
                upd.Position = board.InversePosition(upd.Position);
            }
        }
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
