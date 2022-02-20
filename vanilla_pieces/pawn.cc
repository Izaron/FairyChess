#include "pawn.h"

namespace NFairyChess::NVanillaPieces {

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
        // check move position for correctness
        auto movePosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = 0, .Row = dist});
        if (!movePosition) {
            break;
        }

        // break if this square is blocked by another piece
        if (!ctx.Board.GetBoardPiece(*movePosition).IsEmpty()) {
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
        updates.emplace_back(*movePosition, TBoardPiece::CreateFromExisting(color, newPawnPiece));
        updates.emplace_back(ctx.Position, EmptyBoardPiece());
    }

    // the pawn can capture a piece diagonally
    for (int deltaCol : {-1, 1}) {
        // check move position for correctness
        auto movePosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = deltaCol, .Row = 1});
        if (!movePosition) {
            continue;
        }

        TPawnPiece newPawnPiece = *this;
        newPawnPiece.GetMoveStatus().SetValue(EMoveStatus::Moved);

        // can only capture existing piece of enemy color
        TBoardPiece enemyBoardPiece = ctx.Board.GetBoardPiece(*movePosition);
        if (!enemyBoardPiece.IsEmpty() && enemyBoardPiece.GetColor() != color) {
            auto& updates = ctx.Moves.emplace_back().Updates;
            updates.emplace_back(*movePosition, TBoardPiece::CreateFromExisting(color, newPawnPiece));
            updates.emplace_back(ctx.Position, EmptyBoardPiece());
        }

        // check if we can capture enemy's pawn en passant
        auto enPassantEnemyPosition = ctx.Board.ShiftPosition(ctx.Position, TBoardPosition{.Column = deltaCol, .Row = 0});
        TBoardPiece enPassantBoardPiece = ctx.Board.GetBoardPiece(*enPassantEnemyPosition);
        if (!enPassantBoardPiece.IsEmpty() && enPassantBoardPiece.GetColor() != color) {
            if (auto pawnOrEmpty = enPassantBoardPiece.GetPieceOrEmpty<TPawnPiece>(); !pawnOrEmpty.IsEmpty()) {
                const EMoveStatus enemyMoveStatus = pawnOrEmpty.GetPiece().GetMoveStatus().GetValue<EMoveStatus>();
                if (enemyMoveStatus == EMoveStatus::CanBeCapturedEnPassant) {
                    // we can capture en passant!
                    auto& updates = ctx.Moves.emplace_back().Updates;
                    updates.emplace_back(*movePosition, TBoardPiece::CreateFromExisting(color, newPawnPiece));
                    updates.emplace_back(ctx.Position, EmptyBoardPiece());
                    updates.emplace_back(*enPassantEnemyPosition, EmptyBoardPiece());
                }
            }
        }
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
