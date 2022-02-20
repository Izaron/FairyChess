#include "move_generator.h"
#include "piece_registry.h"

namespace NFairyChess {

TMoveBuilder& TMoveBuilder::SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece) {
    Move_.Updates.emplace_back(position, boardPiece);
    return *this;
}

TMoveBuilder& TMoveBuilder::RemoveBoardPiece(TBoardPosition position) {
    return SetBoardPiece(position, EmptyBoardPiece());
}

TMove TMoveBuilder::Build() {
    return std::move(Move_);
}

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

    for (TBoard::TBoardPieceWithPosition iter : newBoard) {
        TBoardPiece& boardPiece = iter.BoardPiece;
        const TPieceInfo* pieceInfo = TPieceRegistry::GetPieceInfo(boardPiece.GetPieceId());
        if (pieceInfo->AfterMoveApplyFn && pieceInfo->AfterMoveApplyFn(boardPiece)) {
            newBoard.SetBoardPiece(iter.Position, boardPiece);
        }
    }

    return newBoard;
}

} // namespace NFairyChess
