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

class TMoveBuilder {
public:
    TMoveBuilder& SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece);
    TMoveBuilder& RemoveBoardPiece(TBoardPosition position);
    TMove Build();

private:
    TMove Move_;
};

using TMoveContainer = std::vector<TMove>;

struct TMoveContext {
    // new moves should be written here
    TMoveContainer& Moves;

    // used to "look around" to see other pieces
    TOrientedBoard Board;

    // additional info about current piece
    TBoardPosition Position;
};

TMoveContainer GenerateMoves(const TBoard& board, EPieceColor piecesColor);

TBoard ApplyMove(const TBoard& board, const TMove& move);

// helper functions for move generating
enum class EMoveType {
    Leaper,
    Rider,
};
void AddStandardMoves(TMoveContext& ctx, EMoveType moveType, TBoardPosition deltaPosition);

} // namespace NFairyChess
