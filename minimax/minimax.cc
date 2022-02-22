#include "minimax.h"
#include "evaluator.h"
#include "king_piece.h"

#include <limits>
#include <iostream>

namespace NFairyChess {

namespace {

bool CanCaptureKing(const TBoard& board, const TMove& move) {
    int kingsBalance = 0;
    for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
        const TBoardUpdate& update = move.Updates[i];
        if (board.GetBoardPiece(update.Position).GetPieceId() == NVanillaPieces::TKingPiece::PieceId) {
            --kingsBalance;
        }
        if (TBoardPiece{update.NewBoardPiece}.GetPieceId() == NVanillaPieces::TKingPiece::PieceId) {
            ++kingsBalance;
        }
    }
    return kingsBalance != 0;
}

bool CanCaptureKing(const TBoard& board, const TMoveContainer& moveContainer) {
    for (std::size_t i = 0; i < moveContainer.MovesCount; ++i) {
        if (CanCaptureKing(board, moveContainer.Moves[i])) {
            return true;
        }
    }
    return false;
}

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
            /* prolongatedDepth = */ 0);
    PreviousAnalyzedBoards_ = AnalyzedBoards_;
    return BestMove_;
}

int TMinimax::GetAnalyzedBoards() const {
    return AnalyzedBoards_;
}

int TMinimax::FindBestScore(const TBoard& board, EPieceColor color,
                            int depth, int alpha, int beta, int prolongatedDepth) {
    std::size_t hash = board.CalculateHash(depth);
    if (auto iter = HashedScores_.find(hash); iter != HashedScores_.end()) {
        return iter->second;
    }
    ++AnalyzedBoards_;

    if ((depth <= 0 && !prolongatedDepth) || depth <= -6) {
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
        int newProlongatedDepth = std::max(0, prolongatedDepth - 1);
        if (newBoardPieceScore != currentBoardPieceScore) {
            newProlongatedDepth = std::max(newProlongatedDepth, 1);
        }

        //if (!newProlongatedDepth && depth - 1 <= 0) {
            // we can prolongate if we made a check
            //TMoveContainer nextMoveContainer = GenerateMoves(newBoard, color);
            //if (CanCaptureKing(newBoard, nextMoveContainer)) {
                //newProlongatedDepth = 2;
            //}
        //}

        //if (!newProlongatedDepth && AnalyzedBoards_ - PreviousAnalyzedBoards_ >= 15 * 60000) {
            //continue;
        //}

        int score = FindBestScore(newBoard, InvertPieceColor(color), depth - 1,
                                  alpha, beta, newProlongatedDepth);
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
