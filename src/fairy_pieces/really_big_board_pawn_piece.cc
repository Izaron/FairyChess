#include "really_big_board_pawn_piece.h"
#include "queen_piece.h"
#include "rook_piece.h"
#include "knight_piece.h"
#include "bishop_piece.h"

using namespace NFairyChess::NVanillaPieces;

namespace NFairyChess::NFairyPieces {

using enum TReallyBigBoardPawnPiece::EMoveStatus;

namespace {

void AddMoveWithPromotionCheck(TReallyBigBoardPawnPiece pawnPiece, TMoveContext& ctx,
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

bool TryAddForwardMove(TReallyBigBoardPawnPiece pawnPiece, TMoveContext& ctx, int dist) {
    // check move position for correctness
    TBoardPosition movePosition = ctx.Position;
    if (!ctx.Board.ShiftPosition(movePosition, TBoardPosition{.Column = 0, .Row = dist})) {
        return false;
    }

    // break if this square is blocked by another piece
    if (!ctx.Board.GetBoardPiece(movePosition).IsEmpty()) {
        return false;
    }

    // we can move there! update the move status and add the move
    if (dist == 2) {
        pawnPiece.GetMoveStatus().SetValue(JustMovedTwoSquares);
    } else {
        pawnPiece.GetMoveStatus().SetValue(Moved);
    }

    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();
    AddMoveWithPromotionCheck(pawnPiece, ctx, movePosition, color);
    return true;
}

void TryAddSimpleCapturingMove(TReallyBigBoardPawnPiece pawnPiece, TMoveContext& ctx,
                               TBoardPosition movePosition, EPieceColor currentColor)
{
    TBoardPiece enemyBoardPiece = ctx.Board.GetBoardPiece(movePosition);
    if (!enemyBoardPiece.IsEmpty() && enemyBoardPiece.GetColor() != currentColor) {
        AddMoveWithPromotionCheck(pawnPiece, ctx, movePosition, currentColor);
    }
}

void TryAddEnPassantCapturingMove(TReallyBigBoardPawnPiece pawnPiece, TMoveContext& ctx, TBoardPosition movePosition,
                                  TBoardPosition enPassantPosition, EPieceColor currentColor)
{
    TBoardPiece enPassantBoardPiece = ctx.Board.GetBoardPiece(enPassantPosition);
    if (!enPassantBoardPiece.IsEmpty() && enPassantBoardPiece.GetColor() != currentColor) {
        if (auto pawnOrEmpty = enPassantBoardPiece.GetPieceOrEmpty<TReallyBigBoardPawnPiece>(); !pawnOrEmpty.IsEmpty()) {
            const TReallyBigBoardPawnPiece::EMoveStatus enemyMoveStatus =
                pawnOrEmpty.GetPiece().GetMoveStatus().GetValue<TReallyBigBoardPawnPiece::EMoveStatus>();
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

void TryAddCapturingMove(TReallyBigBoardPawnPiece pawnPiece, TMoveContext& ctx, int deltaCol) {
    // check move position for correctness
    TBoardPosition movePosition = ctx.Position;
    if (!ctx.Board.ShiftPosition(movePosition, TBoardPosition{.Column = deltaCol, .Row = 1})) {
        return;
    }

    pawnPiece.GetMoveStatus().SetValue(Moved);
    const EPieceColor color = ctx.Board.GetBoardPiece(ctx.Position).GetColor();

    // can only capture existing piece of enemy color
    TryAddSimpleCapturingMove(pawnPiece, ctx, movePosition, color);

    // check if we can capture enemy's pawn en passant
    TBoardPosition enPassantPosition = ctx.Position;
    ctx.Board.ShiftPosition(enPassantPosition, TBoardPosition{.Column = deltaCol, .Row = 0});
    TryAddEnPassantCapturingMove(pawnPiece, ctx, movePosition, enPassantPosition, color);
}

} // namespace

void TReallyBigBoardPawnPiece::FillMoves(TMoveContext& ctx) {
    TBoardPiece boardPiece = ctx.Board.GetBoardPiece(ctx.Position);
    const EPieceColor color = boardPiece.GetColor();

    const EMoveStatus moveStatus = GetMoveStatus().GetValue<EMoveStatus>();

    // the pawn can move two squares forward if it has not moved yet
    int maxDistance = 1;
    if (moveStatus == EMoveStatus::NotMoved) {
        maxDistance = 6;
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
}

bool TReallyBigBoardPawnPiece::AfterMoveApply(const TBoard& /* oldBoard */, const TMove& /* move */) {
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

} // namespace NFairyChess::NFairyPieces
