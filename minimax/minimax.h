#pragma once

#include "move_generator.h"

#include <unordered_map>

namespace NFairyChess {

class TMinimax {
public:
    TMinimax(int depth);
    TMove FindBestMove(const TBoard& board, EPieceColor color);
    int GetAnalyzedBoards() const;

private:
    int FindBestScore(const TBoard& board, EPieceColor color, int depth,
                      int alpha, int beta, bool forceSearch);

private:
    const int InitDepth_;
    std::unordered_map<std::size_t, int> HashedScores_;
    TMove BestMove_;
    int AnalyzedBoards_ = 0;
    int PreviousAnalyzedBoards_ = 0;
};

} // namespace NFairyChess
