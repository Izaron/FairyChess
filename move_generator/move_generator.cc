#include "move_generator.h"
#include "piece_registry.h"

namespace NFairyChess {

TMoveBuilder& TMoveBuilder::SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece) {
    Move_.Updates[Move_.UpdatesCount++] = {position, boardPiece};
    return *this;
}

TMoveBuilder& TMoveBuilder::RemoveBoardPiece(TBoardPosition position) {
    return SetBoardPiece(position, EmptyBoardPiece());
}

TMove TMoveBuilder::Build() {
    return std::move(Move_);
}

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor) {
    TMoveContainer moveContainer;
    const bool isInverted = piecesColor == EPieceColor::Black;
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
        for (std::size_t moveNum = 0; moveNum < moveContainer.MovesCount; ++moveNum) {
            auto& move = moveContainer.Moves[moveNum];
            for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
                move.Updates[i].Position = board.InversePosition(move.Updates[i].Position);
            }
        }
    }

    return moveContainer;
}

TBoard ApplyMove(const TBoard& board, const TMove& move) {
    TBoard newBoard = board;
    for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
        auto& upd = move.Updates[i];
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

void AddStandardMoves(TMoveContext& ctx, EMoveType moveType, TBoardPosition deltaPosition) {
    TBoardPosition currentPosition = ctx.Position;
    TBoardPiece boardPiece = ctx.Board.GetBoardPiece(currentPosition);
    const EPieceColor color = boardPiece.GetColor();

    while (true) {
        auto optionalPosition = ctx.Board.ShiftPosition(currentPosition, deltaPosition);
        if (!optionalPosition) {
            break;
        }
        currentPosition = *optionalPosition;

        TMove move = TMoveBuilder{}
            .SetBoardPiece(currentPosition, boardPiece)
            .RemoveBoardPiece(ctx.Position)
            .Build();

        TBoardPiece currentPositionBoardPiece = ctx.Board.GetBoardPiece(currentPosition);
        auto& moveContainer = ctx.Moves;
        if (currentPositionBoardPiece.IsEmpty()) {
            moveContainer.Add(std::move(move));
        } else if (currentPositionBoardPiece.GetColor() != color) {
            // capture the enemy piece, but don't move further
            moveContainer.Add(std::move(move));
            break;
        } else {
            // there is friendly piece, can't move here
            break;
        }

        if (moveType != EMoveType::Rider) {
            break;
        }
    }
}

} // namespace NFairyChess
