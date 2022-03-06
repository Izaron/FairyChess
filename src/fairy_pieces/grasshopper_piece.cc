#include "grasshopper_piece.h"

namespace NFairyChess::NFairyPieces {

void TGrasshopperPiece::FillMoves(TMoveContext& moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add hopper moves in any direction
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, boardPiece, EMoveType::Hopper,
                             {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

} // namespace NFairyChess::NFairyPieces
