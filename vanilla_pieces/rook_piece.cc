#include "rook_piece.h"

namespace NFairyChess::NVanillaPieces {

void TRookPiece::FillMoves(TMoveContext moveContext) {
    AddStandardMoves(moveContext, EMoveType::Rider, {-1, 0});
    AddStandardMoves(moveContext, EMoveType::Rider, {1, 0});
    AddStandardMoves(moveContext, EMoveType::Rider, {0, -1});
    AddStandardMoves(moveContext, EMoveType::Rider, {0, 1});
}

} // namespace NFairyChess::NVanillaPieces
