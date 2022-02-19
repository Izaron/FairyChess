#pragma once

#include "board.h"

namespace NFairyChess {

struct TBoardUpdate {
    TBoardPosition Position;
    TBoardPiece NewBoardPiece;
};

struct TMove {
    std::vector<TBoardUpdate> Updates;
};

using TMoveContainer = std::vector<TMove>;

struct TMoveContext {
    // new moves should be written here
    TMoveContainer& Moves;

    // used to "look around" to see other pieces
    const TBoard& Board;

    // additional info about current piece
    EPieceColor Color;
    TBoardPosition Position;
};

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor);

TBoard ApplyMove(const TBoard& board, const TMove& move);

} // namespace NFairyChess
