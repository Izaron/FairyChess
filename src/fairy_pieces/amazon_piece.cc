#include "amazon_piece.h"

namespace NFairyChess::NFairyPieces {

void TAmazonPiece::FillMoves(TMoveContext moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add queen moves
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, boardPiece, EMoveType::Rider,
                             {.Column = deltaCol, .Row = deltaRow});
        }
    }

    // add knight moves
    for (int colMult : {-1, 1}) {
        for (int rowMult : {-1, 1}) {
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = colMult * 2, .Row = rowMult * 1});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = colMult * 1, .Row = rowMult * 2});
        }
    }
}

} // namespace NFairyChess::NFairyPieces
