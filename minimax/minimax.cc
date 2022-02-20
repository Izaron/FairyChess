#include "minimax.h"
#include "evaluator.h"

#include <limits>

namespace NFairyChess {

namespace {

using TMoveAndScore = std::pair<TMove, int>;

int EvaluateScore(const TBoard& board) {
    TEvaluationResult eval = Evaluate(board);
    return (eval.WhiteCost - eval.BlackCost) +
        5 * (eval.WhiteAvailableMoves - eval.BlackAvailableMoves);
}

int GetInitialScore(EPieceColor color) {
    return color == EPieceColor::White ?
        std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
}

void UpdateBestScore(int& bestScore, int newScore, EPieceColor color) {
    if (color == EPieceColor::White) {
        bestScore = std::max(bestScore, newScore);
    } else {
        bestScore = std::min(bestScore, newScore);
    }
}

} // namespace

TMinimax::TMinimax(int depth)
    : InitDepth_{depth}
{
}

TMove TMinimax::FindBestMove(const TBoard& board, EPieceColor color) {
    FindBestScore(board, color, InitDepth_,
            /* alpha = */ std::numeric_limits<int>::min(),
            /* beta = */ std::numeric_limits<int>::max());
    return BestMove_;
}

int TMinimax::GetAnalyzedBoards() const {
    return AnalyzedBoards_;
}

int TMinimax::FindBestScore(const TBoard& board, EPieceColor color,
                            int depth, int alpha, int beta) {
    std::size_t hash = board.CalculateHash(depth);
    if (auto iter = HashedScores_.find(hash); iter != HashedScores_.end()) {
        return iter->second;
    }
    ++AnalyzedBoards_;

    if (depth <= 0) {
        // terminal level, return only score
        int score = EvaluateScore(board);
        return score;
    }

    int bestScore = GetInitialScore(color);

    TMoveContainer moveContainer = GenerateMoves(board, color);
    for (std::size_t i = 0; i < moveContainer.MovesCount; ++i) {
        auto& move = moveContainer.Moves[i];
        TBoard newBoard = ApplyMove(board, move);
        int score = FindBestScore(newBoard, InvertPieceColor(color), depth - 1,
                                  alpha, beta);
        UpdateBestScore(bestScore, score, color);

        if (bestScore == score && depth == InitDepth_) {
            BestMove_ = std::move(move);
        }

        if (color == EPieceColor::White) {
            alpha = std::max(alpha, bestScore);
        } else {
            beta = std::min(beta, bestScore);
        }
        if (beta < alpha) {
            break;
        }
    }

    return bestScore;
}

} // namespace NFairyChess
