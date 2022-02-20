#include "king_piece.h"

namespace NFairyChess::NVanillaPieces {

void TKingPiece::FillMoves(TMoveContext moveContext) {
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, EMoveType::Leaper, {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
