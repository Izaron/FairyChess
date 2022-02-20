#include "pawn.h"

namespace NFairyChess::NVanillaPieces {

using enum TPawnPiece::EMoveStatus;

namespace {

bool TryAddForwardMove(TPawnPiece pawnPiece, TMoveContext& ctx, int dist) {
    // check move position for correctness
    auto movePosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = 0, .Row = dist});
    if (!movePosition) {
        return false;
    }

    // break if this square is blocked by another piece
    if (!ctx.Board.GetBoardPiece(*movePosition).IsEmpty()) {
        return false;
    }

    // we can move there! update the move status and add the move
    if (dist == 2) {
        pawnPiece.GetMoveStatus().SetValue(JustMovedTwoSquares);
    } else {
        pawnPiece.GetMoveStatus().SetValue(Moved);
    }

    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();
    ctx.Moves.push_back(
        TMoveBuilder{}
            .SetBoardPiece(*movePosition, TBoardPiece::CreateFromExisting(color, pawnPiece))
            .RemoveBoardPiece(ctx.Position)
            .Build()
    );
    return true;
}

void TryAddSimpleCapturingMove(TPawnPiece pawnPiece, TMoveContext& ctx,
                               TBoardPosition movePosition, EPieceColor currentColor)
{
    TBoardPiece enemyBoardPiece = ctx.Board.GetBoardPiece(movePosition);
    if (!enemyBoardPiece.IsEmpty() && enemyBoardPiece.GetColor() != currentColor) {
        ctx.Moves.push_back(
            TMoveBuilder{}
                .SetBoardPiece(movePosition, TBoardPiece::CreateFromExisting(currentColor, pawnPiece))
                .RemoveBoardPiece(ctx.Position)
                .Build()
        );
    }
}

void TryAddEnPassantCapturingMove(TPawnPiece pawnPiece, TMoveContext& ctx, TBoardPosition movePosition,
                                  TBoardPosition enPassantPosition, EPieceColor currentColor)
{
    TBoardPiece enPassantBoardPiece = ctx.Board.GetBoardPiece(enPassantPosition);
    if (!enPassantBoardPiece.IsEmpty() && enPassantBoardPiece.GetColor() != currentColor) {
        if (auto pawnOrEmpty = enPassantBoardPiece.GetPieceOrEmpty<TPawnPiece>(); !pawnOrEmpty.IsEmpty()) {
            const TPawnPiece::EMoveStatus enemyMoveStatus =
                pawnOrEmpty.GetPiece().GetMoveStatus().GetValue<TPawnPiece::EMoveStatus>();
            if (enemyMoveStatus == CanBeCapturedEnPassant) {
                // we can capture en passant!
                ctx.Moves.push_back(
                    TMoveBuilder{}
                        .SetBoardPiece(movePosition, TBoardPiece::CreateFromExisting(currentColor, pawnPiece))
                        .RemoveBoardPiece(enPassantPosition)
                        .RemoveBoardPiece(ctx.Position)
                        .Build()
                );
            }
        }
    }
}

void TryAddCapturingMove(TPawnPiece pawnPiece, TMoveContext& ctx, int deltaCol) {
    // check move position for correctness
    auto movePosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = deltaCol, .Row = 1});
    if (!movePosition) {
        return;
    }

    pawnPiece.GetMoveStatus().SetValue(Moved);
    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();

    // can only capture existing piece of enemy color
    TryAddSimpleCapturingMove(pawnPiece, ctx, *movePosition, color);

    // check if we can capture enemy's pawn en passant
    auto enPassantPosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = deltaCol, .Row = 0});
    TryAddEnPassantCapturingMove(pawnPiece, ctx, *movePosition, *enPassantPosition, color);
}

} // namespace

void TPawnPiece::FillMoves(TMoveContext ctx) {
    TBoardPiece boardPiece = ctx.Board.GetBoardPiece(ctx.Position);
    const EPieceColor color = boardPiece.GetColor();

    const EMoveStatus moveStatus = GetMoveStatus().GetValue<EMoveStatus>();

    // the pawn can move two squares forward if it has not moved yet
    int maxDistance = 1;
    if (moveStatus == EMoveStatus::NotMoved) {
        maxDistance = 2;
    }

    for (int dist = 1; dist <= maxDistance; ++dist) {
        if (!TryAddForwardMove(*this, ctx, dist)) {
            break;
        }
    }

    // the pawn can capture a piece diagonally
    for (int deltaCol : {-1, 1}) {
        TryAddCapturingMove(*this, ctx, deltaCol);
    }

    // TODO: make pawn promotion
}

bool TPawnPiece::AfterMoveApply() {
    auto moveStatus = GetMoveStatus();
    switch (moveStatus.GetValue<EMoveStatus>()) {
        case EMoveStatus::JustMovedTwoSquares: {
            moveStatus.SetValue(EMoveStatus::CanBeCapturedEnPassant);
            return true;
        }
        case EMoveStatus::CanBeCapturedEnPassant: {
            moveStatus.SetValue(EMoveStatus::Moved);
            return true;
        }
        default: {
            return false;
        }
    }
};

} // namespace NFairyChess::NVanillaPieces
