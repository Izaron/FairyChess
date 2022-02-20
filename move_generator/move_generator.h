#pragma once

#include "board.h"

#include <array>

namespace NFairyChess {

struct TBoardUpdate {
    TBoardPosition Position;
    TBoardPiece NewBoardPiece;
};

struct TMove {
    std::array<TBoardUpdate, 10> Updates;
    std::size_t UpdatesCount = 0;
};

class TMoveBuilder {
public:
    TMoveBuilder& SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece);
    TMoveBuilder& RemoveBoardPiece(TBoardPosition position);
    TMove Build();

private:
    TMove Move_;
};

struct TMoveContainer {
    std::array<TMove, 128> Moves;
    std::size_t MovesCount = 0;

    void Add(TMove move) {
        Moves[MovesCount++] = std::move(move);
    }
};

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
