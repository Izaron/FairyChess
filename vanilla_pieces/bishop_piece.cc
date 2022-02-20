#include "bishop_piece.h"

namespace NFairyChess::NVanillaPieces {

void TBishopPiece::FillMoves(TMoveContext moveContext) {
    for (int colDelta : {-1, 1}) {
        for (int rowDelta : {-1, 1}) {
            AddStandardMoves(moveContext, EMoveType::Rider, {.Column = colDelta, .Row = rowDelta});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
