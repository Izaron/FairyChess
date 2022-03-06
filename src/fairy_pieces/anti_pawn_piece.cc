#include "anti_pawn_piece.h"
#include "queen_piece.h"
#include "rook_piece.h"
#include "knight_piece.h"
#include "bishop_piece.h"

using namespace NFairyChess::NVanillaPieces;

namespace NFairyChess::NFairyPieces {

using enum TAntiPawnPiece::EMoveStatus;

namespace {

void AddMoveWithPromotionCheck(TAntiPawnPiece pawnPiece, TMoveContext& ctx,
                               TBoardPosition movePosition, EPieceColor color)
{
    if (movePosition.Row == ctx.Board.GetRows() - 1) {
        // a pawn on the last row should be promoted to a valuable piece
        std::array<TBoardPiece, 4> arr = {
            TBoardPiece::Create<TQueenPiece>(color),
            TBoardPiece::Create<TRookPiece>(color),
            TBoardPiece::Create<TKnightPiece>(color),
            TBoardPiece::Create<TBishopPiece>(color),
        };
        for (TBoardPiece boardPiece : arr) {
            ctx.Moves.Add(
                TMoveBuilder{}
                    .SetBoardPiece(movePosition, boardPiece)
                    .RemoveBoardPiece(ctx.Position)
                    .Build()
            );
        }
    } else {
        ctx.Moves.Add(
            TMoveBuilder{}
                .SetBoardPiece(movePosition, TBoardPiece::CreateFromExisting(color, pawnPiece))
                .RemoveBoardPiece(ctx.Position)
                .Build()
        );
    }
}

bool TryAddDiagonalMove(TAntiPawnPiece pawnPiece, TMoveContext& ctx, TBoardPosition delta) {
    // check move position for correctness
    TBoardPosition movePosition = ctx.Position;
    if (!ctx.Board.ShiftPosition(movePosition, delta)) {
        return false;
    }

    // break if this square is blocked by another piece
    if (!ctx.Board.GetBoardPiece(movePosition).IsEmpty()) {
        return false;
    }

    // we can move there! update the move status and add the move
    if (delta.Row == 2) {
        pawnPiece.GetMoveStatus().SetValue(JustMovedTwoSquares);
    } else {
        pawnPiece.GetMoveStatus().SetValue(Moved);
    }

    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();
    AddMoveWithPromotionCheck(pawnPiece, ctx, movePosition, color);
    return true;
}

void TryAddSimpleCapturingMove(TAntiPawnPiece pawnPiece, TMoveContext& ctx,
                               TBoardPosition movePosition, EPieceColor currentColor)
{
    TBoardPiece enemyBoardPiece = ctx.Board.GetBoardPiece(movePosition);
    if (!enemyBoardPiece.IsEmpty() && enemyBoardPiece.GetColor() != currentColor) {
        AddMoveWithPromotionCheck(pawnPiece, ctx, movePosition, currentColor);
    }
}

void TryAddEnPassantCapturingMove(TAntiPawnPiece pawnPiece, TMoveContext& ctx, TBoardPosition movePosition,
                                  TBoardPosition enPassantPosition, EPieceColor currentColor)
{
    TBoardPiece enPassantBoardPiece = ctx.Board.GetBoardPiece(enPassantPosition);
    if (!enPassantBoardPiece.IsEmpty() && enPassantBoardPiece.GetColor() != currentColor) {
        if (auto pawnOrEmpty = enPassantBoardPiece.GetPieceOrEmpty<TAntiPawnPiece>(); !pawnOrEmpty.IsEmpty()) {
            const TAntiPawnPiece::EMoveStatus enemyMoveStatus =
                pawnOrEmpty.GetPiece().GetMoveStatus().GetValue<TAntiPawnPiece::EMoveStatus>();
            if (enemyMoveStatus == CanBeCapturedEnPassant) {
                // we can capture en passant!
                ctx.Moves.Add(
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

void TryAddCapturingMove(TAntiPawnPiece pawnPiece, TMoveContext& ctx) {
    // check move position for correctness
    TBoardPosition movePosition = ctx.Position;
    if (!ctx.Board.ShiftPosition(movePosition, TBoardPosition{.Column = 0, .Row = 1})) {
        return;
    }

    pawnPiece.GetMoveStatus().SetValue(Moved);
    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();

    // can only capture existing piece of enemy color
    TryAddSimpleCapturingMove(pawnPiece, ctx, movePosition, color);

    // check if we can capture enemy's pawn en passant
    for (int deltaCol : {-1, 1}) {
        TBoardPosition enPassantPosition = ctx.Position;
        ctx.Board.ShiftPosition(enPassantPosition, TBoardPosition{.Column = deltaCol, .Row = 0});
        TryAddEnPassantCapturingMove(pawnPiece, ctx, movePosition, enPassantPosition, color);
    }
}

} // namespace

void TAntiPawnPiece::FillMoves(TMoveContext& ctx) {
    TBoardPiece boardPiece = ctx.Board.GetBoardPiece(ctx.Position);
    const EPieceColor color = boardPiece.GetColor();

    const EMoveStatus moveStatus = GetMoveStatus().GetValue<EMoveStatus>();

    // the pawn can move two squares DIAGONALLY if it has not moved yet
    int maxDistance = 1;
    if (moveStatus == EMoveStatus::NotMoved) {
        maxDistance = 2;
    }

    for (int direction : {-1, 1}) {
        for (int dist = 1; dist <= maxDistance; ++dist) {
            if (!TryAddDiagonalMove(*this, ctx, {.Column = dist * direction, .Row = dist})) {
                break;
            }
        }
    }

    // the pawn can capture a piece FORWARD
    TryAddCapturingMove(*this, ctx);
}

bool TAntiPawnPiece::AfterMoveApply() {
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
