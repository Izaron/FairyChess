#include "unicorn_piece.h"

namespace NFairyChess::NFairyPieces {

void TUnicornPiece::FillMoves(TMoveContext moveContext) {
    // add knight and zebra moves
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);
    for (int dist : {2, 3}) {
        for (int colMult : {-1, 1}) {
            for (int rowMult : {-1, 1}) {
                AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                                 {.Column = colMult * dist, .Row = rowMult * 1});
                AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                                 {.Column = colMult * 1, .Row = rowMult * dist});
            }
        }
    }
}

} // namespace NFairyChess::NFairyPieces
