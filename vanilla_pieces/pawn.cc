#include "pawn.h"

namespace NFairyChess::NVanillaPieces {

void TPawnPiece::FillMoves(TMoveContext ctx) {
    TBoardPiece boardPiece = TBoardPiece::CreateFromExisting(ctx.Color, *this);

    // move 1 square "forward" if this is not blocked
    auto simpleMovePosition = ctx.Board.ShiftPosition(ctx.Position, {.Column = 0, .Row = 1});
    if (!simpleMovePosition) {
        return;
    }
    if (!ctx.Board.GetBoardPiece(*simpleMovePosition, ctx.Color).IsEmpty()) {
        return;
    }
    auto& updates = ctx.Moves.emplace_back().Updates;
    updates.emplace_back(*simpleMovePosition, boardPiece);
    updates.emplace_back(ctx.Position, EmptyBoardPiece());
}

} // namespace NFairyChess::NVanillaPieces
