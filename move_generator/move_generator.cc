#include "move_generator.h"

namespace NFairyChess {

std::vector<TMove> GenerateMoves(const TBoard& board, EPieceColor piecesColor) {
    for (TBoardPiece boardPiece : board) {
        if (boardPiece.GetColor() != piecesColor) {
            continue;
        }
        // TODO: generate moves...
    }
}

} // namespace NFairyChess
