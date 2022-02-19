#include "move_generator.h"

namespace NFairyChess {

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor) {
    TMoveContainer moveContainer;
    for (auto iter : board) {
        auto& boardPiece = iter.BoardPiece;
        if (boardPiece.GetColor() != piecesColor) {
            continue;
        }
        // TODO: generate moves...
    }
    return moveContainer;
}

} // namespace NFairyChess
