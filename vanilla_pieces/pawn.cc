#include "pawn.h"

namespace NFairyChess::NVanillaPieces {

void TPawnPiece::FillMoves(TMoveContext ctx) {
    TBoardPiece boardPiece = TBoardPiece::CreateFromExisting(ctx.Color, *this);

    // move 1 square "forward"
    auto newPosition = ctx.Board.ShiftPosition(ctx.Position, {0, 1});
    if (newPosition) {
        auto& updates = ctx.Moves.emplace_back().Updates;
        updates.emplace_back(*newPosition, boardPiece);
        updates.emplace_back(ctx.Position, EmptyBoardPiece());
    }
}

} // namespace NFairyChess::NVanillaPieces
