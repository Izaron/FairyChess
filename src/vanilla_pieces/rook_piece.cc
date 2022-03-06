#include "rook_piece.h"

namespace NFairyChess::NVanillaPieces {

void TRookPiece::FillMoves(TMoveContext& moveContext) {
    // mark the rook as "moved"
    TRookPiece newRookPiece = *this;
    newRookPiece.GetMoveStatus().SetValue(EMoveStatus::Moved);
    const EPieceColor color = moveContext.Board.GetBoardPiece(moveContext.Position).GetColor();
    TBoardPiece newBoardPiece = TBoardPiece::CreateFromExisting(color, newRookPiece);

    // add standard rook moves
    AddStandardMoves(moveContext, newBoardPiece, EMoveType::Rider, {-1, 0});
    AddStandardMoves(moveContext, newBoardPiece, EMoveType::Rider, {1, 0});
    AddStandardMoves(moveContext, newBoardPiece, EMoveType::Rider, {0, -1});
    AddStandardMoves(moveContext, newBoardPiece, EMoveType::Rider, {0, 1});
}

} // namespace NFairyChess::NVanillaPieces
