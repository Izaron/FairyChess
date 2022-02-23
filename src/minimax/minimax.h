#pragma once

#include "move_generator.h"

#include <variant>
#include <unordered_set>

namespace NFairyChess {

enum class EGameEnd {
    Checkmate, // any move will lead to defeat, and the enemy is attacking the king
    Stalemate, // same as above, but the enemy is not attacking the king
};

class TMinimax {
public:
    TMinimax(int depth);
    std::variant<TMove, EGameEnd> FindBestMoveOrGameEnd(const TBoard& board, EPieceColor color);
    int GetAnalyzedBoards() const;

private:
    int FindBestScore(const TBoard& board, EPieceColor color, int depth,
                      int alpha, int beta, int prolongatedDepth);

private:
    const int InitDepth_;
    // FIXME: resurrect Zobrist hashing?
    std::unordered_set<uint32_t> CommitedBoards_;
    TMove BestMove_;
    int AnalyzedBoards_ = 0;
    int PreviousAnalyzedBoards_ = 0;
};

} // namespace NFairyChess
