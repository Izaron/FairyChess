#include "knight.h"

namespace NFairyChess::NVanillaPieces {

namespace {

enum class EMoveType {
    Leaper,
    Rider,
};

void AddMoves(TMoveContext& ctx, EMoveType moveType, TBoardPosition deltaPosition) {
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
        if (currentPositionBoardPiece.IsEmpty()) {
            ctx.Moves.push_back(std::move(move));
        } else if (currentPositionBoardPiece.GetColor() != color) {
            // capture the enemy piece, but don't move further
            ctx.Moves.push_back(std::move(move));
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

} // namespace

void TKnightPiece::FillMoves(TMoveContext moveContext) {
    constexpr std::array<TBoardPosition, 8> DeltaPositions = {{
        {.Column = 1, .Row = 2},
        {.Column = 2, .Row = 1},
        {.Column = -1, .Row = 2},
        {.Column = 2, .Row = -1},
        {.Column = 1, .Row = -2},
        {.Column = -2, .Row = 1},
        {.Column = -1, .Row = -2},
        {.Column = -2, .Row = -1},
    }};
    for (TBoardPosition deltaPosition : DeltaPositions) {
        AddMoves(moveContext, EMoveType::Leaper, deltaPosition);
    }
}

} // namespace NFairyChess::NVanillaPieces
