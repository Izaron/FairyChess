#include "empress_piece.h"

namespace NFairyChess::NFairyPieces {

void TEmpressPiece::FillMoves(TMoveContext& moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add rook moves
    AddStandardMoves(moveContext, boardPiece, EMoveType::Rider, {-1, 0});
    AddStandardMoves(moveContext, boardPiece, EMoveType::Rider, {1, 0});
    AddStandardMoves(moveContext, boardPiece, EMoveType::Rider, {0, -1});
    AddStandardMoves(moveContext, boardPiece, EMoveType::Rider, {0, 1});

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
