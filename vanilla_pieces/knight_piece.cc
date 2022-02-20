#include "knight_piece.h"

namespace NFairyChess::NVanillaPieces {

void TKnightPiece::FillMoves(TMoveContext moveContext) {
    for (int colMult : {-1, 1}) {
        for (int rowMult : {-1, 1}) {
            AddStandardMoves(moveContext, EMoveType::Leaper, {.Column = colMult * 2, .Row = rowMult * 1});
            AddStandardMoves(moveContext, EMoveType::Leaper, {.Column = colMult * 1, .Row = rowMult * 2});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
