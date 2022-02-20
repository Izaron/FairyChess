#pragma once

#include "move_generator.h"

namespace NFairyChess {

class TMinimax {
public:
    TMinimax(const TBoard& board, EPieceColor color, int depth);
    TMove FindBestMove();
    int GetAnalyzedBoards() const;

private:
    int FindBestScore(const TBoard& board, EPieceColor color, int depth, int alpha, int beta);

private:
    const TBoard& InitBoard_;
    const EPieceColor InitColor_;
    const int InitDepth_;
    TMove BestMove_;
    int AnalyzedBoards_ = 0;
};

} // namespace NFairyChess
