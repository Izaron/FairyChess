#include "zebra_piece.h"

namespace NFairyChess::NFairyPieces {

void TZebraPiece::FillMoves(TMoveContext moveContext) {
    // add zebra moves
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);
    for (int colMult : {-1, 1}) {
        for (int rowMult : {-1, 1}) {
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = colMult * 3, .Row = rowMult * 1});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = colMult * 1, .Row = rowMult * 3});
        }
    }
}

} // namespace NFairyChess::NFairyPieces
