#include "pawn.h"

namespace NFairyChess::NVanillaPieces {

void TPawnPiece::FillMoves(TMoveContext ctx) {
    TBoardPiece boardPiece = TBoardPiece::CreateFromExisting(ctx.Color, *this);

    const EMoveStatus moveStatus = GetMoveStatus().GetValue<EMoveStatus>();

    // the pawn can move two squares forward if it has not moved yet
    int maxDistance = 1;
    if (moveStatus == EMoveStatus::NotMoved) {
        maxDistance = 2;
    }

    for (int dist = 1; dist <= maxDistance; ++dist) {
        // check move position for correctness
        auto movePosition = ctx.Board.ShiftPosition(ctx.Position, {.Column = 0, .Row = dist});
        if (!movePosition) {
            break;
        }

        // break if this square is blocked by another piece
        if (!ctx.Board.GetBoardPiece(*movePosition, ctx.Color).IsEmpty()) {
            break;
        }

        // we can move there! update the move status and add the move
        TPawnPiece newPawnPiece = *this;
        if (dist == 2) {
            newPawnPiece.GetMoveStatus().SetValue(EMoveStatus::JustMovedTwoSquares);
        } else {
            newPawnPiece.GetMoveStatus().SetValue(EMoveStatus::Moved);
        }

        auto& updates = ctx.Moves.emplace_back().Updates;
        updates.emplace_back(*movePosition, TBoardPiece::CreateFromExisting(ctx.Color, newPawnPiece));
        updates.emplace_back(ctx.Position, EmptyBoardPiece());
    }

    // TODO: attacking other pieces
}

} // namespace NFairyChess::NVanillaPieces
