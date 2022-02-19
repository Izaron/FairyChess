#pragma once

#include "board.h"

namespace NFairyChess {

struct TChange {
    std::size_t Column;
    std::size_t Row;
    TBoardPiece BoardPiece;
};

struct TMove {
    std::vector<TChange> Changes;
};

using TMoveContainer = std::vector<TMove>;

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor);

} // namespace NFairyChess
