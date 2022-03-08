#include "fool_piece.h"

namespace NFairyChess::NFairyPieces {

void TFoolPiece::FillMoves(TMoveContext& moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    for (int deltaCol : {-1, 1}) {
        for (int deltaRow : {-1, 1}) {
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 2, .Row = deltaRow * 1});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 3, .Row = deltaRow * 1});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 3, .Row = deltaRow * 2});

            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 1, .Row = deltaRow * 2});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 1, .Row = deltaRow * 3});
            AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol * 2, .Row = deltaRow * 3});
        }
    }
}

} // namespace NFairyChess::NFairyPieces
