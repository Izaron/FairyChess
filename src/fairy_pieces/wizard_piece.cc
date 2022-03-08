#include "wizard_piece.h"

namespace NFairyChess::NFairyPieces {

void TWizardPiece::FillMoves(TMoveContext& moveContext) {
    static constexpr std::array<TBoardPosition, 8> Shifts = {
        TBoardPosition{.Column = 0, .Row = 2},
        TBoardPosition{.Column = 1, .Row = 1},
        TBoardPosition{.Column = 2, .Row = 0},
        TBoardPosition{.Column = 1, .Row = -1},
        TBoardPosition{.Column = 0, .Row = -2},
        TBoardPosition{.Column = -1, .Row = -1},
        TBoardPosition{.Column = -2, .Row = 0},
        TBoardPosition{.Column = -1, .Row = 1},
    };

    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);
    for (TBoardPosition shift : Shifts) {
        AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper, shift);
    }
}

} // namespace NFairyChess::NFairyPieces
