#pragma once

#include "board.h"

namespace NFairyChess {

struct TBoardUpdate {
    std::size_t Column;
    std::size_t Row;
    TBoardPiece NewBoardPiece;
};

struct TMove {
    std::vector<TBoardUpdate> Changes;
};

using TMoveContainer = std::vector<TMove>;

struct TMoveContext {
    // where new moves should be written
    TMoveContainer& MoveContainer;

    // used to "look around" to see other pieces
    const TBoard& Board;

    // info about current piece
    EPieceColor Color;
    int Column;
    int Row;
};

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor);

} // namespace NFairyChess
