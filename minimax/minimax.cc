#include "minimax.h"
#include "evaluator.h"

#include <limits>
#include <iostream>

namespace NFairyChess {

namespace {

using TMoveAndScore = std::pair<TMove, int>;

int EvaluateScore(const TBoard& board) {
    TEvaluationResult eval = Evaluate(board);
    return (eval.WhiteCost - eval.BlackCost) +
        10 * (eval.WhiteAvailableMoves - eval.BlackAvailableMoves);
}

int GetInitialScore(EPieceColor color) {
    return color == EPieceColor::White ?
        std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
}

int EvaluatePieceScore(const TBoard& board) {
    TEvaluationResult eval = Evaluate(board, /* calculateAvailableMoves = */ false);
    return eval.WhiteCost - eval.BlackCost;
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
            /* beta = */ std::numeric_limits<int>::max(),
            false);
    PreviousAnalyzedBoards_ = AnalyzedBoards_;
    return BestMove_;
}

int TMinimax::GetAnalyzedBoards() const {
    return AnalyzedBoards_;
}

int TMinimax::FindBestScore(const TBoard& board, EPieceColor color,
                            int depth, int alpha, int beta, bool forceSearch) {
    std::size_t hash = board.CalculateHash(depth);
    if (auto iter = HashedScores_.find(hash); iter != HashedScores_.end()) {
        return iter->second;
    }
    ++AnalyzedBoards_;

    if ((depth <= 0 && !forceSearch) || depth <= -6) {
        int score = EvaluateScore(board);
        HashedScores_[hash] = score;
        return score;
    }

    int bestScore = GetInitialScore(color);

    TMoveContainer moveContainer = GenerateMoves(board, color);

    // sort moves by their immediate score
    auto movesBeginIter = std::begin(moveContainer.Moves);
    auto movesEndIter = std::begin(moveContainer.Moves);
    std::advance(movesEndIter, moveContainer.MovesCount);
    std::sort(movesBeginIter, movesEndIter,
        [&board, color](const TMove& oneMove, const TMove& twoMove) {
            const int oneScore = EvaluatePieceScore(ApplyMove(board, oneMove));
            const int twoScore = EvaluatePieceScore(ApplyMove(board, twoMove));
            if (color == EPieceColor::White) {
                return oneScore > twoScore;
            } else {
                return oneScore < twoScore;
            }
        }
    );

    const int currentBoardPieceScore = EvaluatePieceScore(board);

    for (std::size_t i = 0; i < moveContainer.MovesCount; ++i) {
        auto& move = moveContainer.Moves[i];
        TBoard newBoard = ApplyMove(board, move);

        const int newBoardPieceScore = EvaluatePieceScore(newBoard);
        const bool forceSearchNow = newBoardPieceScore != currentBoardPieceScore;

        int score = FindBestScore(newBoard, InvertPieceColor(color), depth - 1,
                                  alpha, beta, forceSearchNow);
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

    HashedScores_[hash] = bestScore;
    return bestScore;
}

} // namespace NFairyChess
