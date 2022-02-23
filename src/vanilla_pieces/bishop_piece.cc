#include "bishop_piece.h"

namespace NFairyChess::NVanillaPieces {

void TBishopPiece::FillMoves(TMoveContext moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);
    for (int colDelta : {-1, 1}) {
        for (int rowDelta : {-1, 1}) {
            AddStandardMoves(moveContext, boardPiece, EMoveType::Rider,
                             {.Column = colDelta, .Row = rowDelta});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
