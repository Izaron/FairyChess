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

struct IMoveContainer {
    ~IMoveContainer() = default;
    virtual void Add(const TMove& move) = 0;
    virtual void InverseMoves(const TBoard& board) = 0;
};

struct TMoveContainer : IMoveContainer {
    std::array<TMove, 128> Moves;
    std::size_t MovesCount = 0;

    void Add(const TMove& move) override {
        Moves[MovesCount++] = move;
    }
    void InverseMoves(const TBoard& board) override;
};

struct TDummyMoveContainer : IMoveContainer {
    std::size_t MovesCount = 0;

    void Add(const TMove& move) override {
        MovesCount++;
    }
    void InverseMoves(const TBoard& /* board */) override {}
};

struct TMoveContext {
    // new moves should be written here
    IMoveContainer& Moves;

    // used to "look around" to see other pieces
    TOrientedBoard Board;

    // additional info about current piece
    const TBoardPosition Position;
};

void GenerateMoves(IMoveContainer& moveContainer, const TBoard& board, EPieceColor piecesColor);

TBoard ApplyMove(const TBoard& board, const TMove& move);

// helper functions for move generating
enum class EMoveType {
    Leaper,
    Rider,
};
void AddStandardMoves(TMoveContext& ctx, TBoardPiece boardPiece, EMoveType moveType, TBoardPosition deltaPosition);

} // namespace NFairyChess
