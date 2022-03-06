#include "princess_piece.h"

namespace NFairyChess::NFairyPieces {

void TPrincessPiece::FillMoves(TMoveContext& moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add bishop moves
    for (int colDelta : {-1, 1}) {
        for (int rowDelta : {-1, 1}) {
            AddStandardMoves(moveContext, boardPiece, EMoveType::Rider,
                             {.Column = colDelta, .Row = rowDelta});
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
