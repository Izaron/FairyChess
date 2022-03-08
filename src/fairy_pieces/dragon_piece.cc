#include "dragon_piece.h"

namespace NFairyChess::NFairyPieces {

void TDragonPiece::FillMoves(TMoveContext& moveContext) {
    TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(moveContext.Position);

    // add vertical and horizontal moves
    {
        static const std::vector<std::pair<int, int>> pairs = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        };
        for (auto [colMult, rowMult] : pairs) {
            for (int delta : {4, 6}) {
                AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                                 {.Column = colMult * delta, .Row = rowMult * delta});
            }
        }
    }

    // add diagonal moves
    {
        static const std::vector<std::pair<int, int>> pairs = {
            {1, 2}, {2, 1}, {3, 3}, {4, 4}, {2, 5}, {5, 2},
        };
        for (int colMult : {-1, 1}) {
            for (int rowMult : {-1, 1}) {
                for (auto [colDelta, rowDelta] : pairs) {
                    AddStandardMoves(moveContext, boardPiece, EMoveType::Leaper,
                                     {.Column = colMult * colDelta, .Row = rowMult * rowDelta});
                }
            }
        }
    }
}

} // namespace NFairyChess::NFairyPieces
