#include "queen_piece.h"

namespace NFairyChess::NVanillaPieces {

void TQueenPiece::FillMoves(TMoveContext moveContext) {
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, EMoveType::Rider, {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
