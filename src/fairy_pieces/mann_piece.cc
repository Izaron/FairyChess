#include "mann_piece.h"

namespace NFairyChess::NFairyPieces {

void TMannPiece::FillMoves(TMoveContext moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add king moves
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

} // namespace NFairyChess::NFairyPieces
