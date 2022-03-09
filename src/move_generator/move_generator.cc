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

void TMoveContainer::InverseMoves(const TBoard& board) {
    for (std::size_t moveNum = 0; moveNum < MovesCount; ++moveNum) {
        auto& move = Moves[moveNum];
        for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
            move.Updates[i].Position = board.InversePosition(move.Updates[i].Position);
        }
    }
}

void GenerateMoves(IMoveContainer& moveContainer, const TBoard& board, EPieceColor piecesColor) {
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
            .Board = TOrientedBoardWrapper{board, isInverted},
            .Position = position,
        };
        pieceInfo->FillMovesFn(boardPiece, ctx);
    }

    // inverse back position for black pieces
    if (isInverted) {
        moveContainer.InverseMoves(board);
    }
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
        if (pieceInfo->AfterMoveApplyFn && pieceInfo->AfterMoveApplyFn(boardPiece, board, move)) {
            newBoard.SetBoardPiece(iter.Position, boardPiece);
        }
    }

    return newBoard;
}

void AddHopperMoves(TMoveContext& ctx, TBoardPiece boardPiece, TBoardPosition deltaPosition) {
    TBoardPosition currentPosition = ctx.Position;
    const EPieceColor color = boardPiece.GetColor();

    bool canMove = false;
    while (true) {
        if (!ctx.Board.ShiftPosition(currentPosition, deltaPosition)) {
            break;
        }
        TBoardPiece curPosBoardPiece = ctx.Board.GetBoardPiece(currentPosition);

        // we had a non-empty board cell previously, check if can hop here
        if (canMove) {
            if (curPosBoardPiece.IsEmpty() || curPosBoardPiece.GetColor() != color) {
                TMove move = TMoveBuilder{}
                    .SetBoardPiece(currentPosition, boardPiece)
                    .RemoveBoardPiece(ctx.Position)
                    .Build();
                ctx.Moves.Add(std::move(move));
            }
            break;
        }

        // if the board cell is not empty, try to hop on next position
        if (!curPosBoardPiece.IsEmpty()) {
            canMove = true;
        }
    }
}

void AddStandardMoves(TMoveContext& ctx, TBoardPiece boardPiece, EMoveType moveType,
                      TBoardPosition deltaPosition)
{
    if (moveType == EMoveType::Hopper) {
        AddHopperMoves(ctx, boardPiece, deltaPosition);
        return;
    }

    TBoardPosition currentPosition = ctx.Position;
    const EPieceColor color = boardPiece.GetColor();

    while (true) {
        if (!ctx.Board.ShiftPosition(currentPosition, deltaPosition)) {
            break;
        }

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
