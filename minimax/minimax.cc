#include "minimax.h"
#include "evaluator.h"
#include "king_piece.h"
#include "pretty_printer.h"

#include <limits>
#include <iostream>

namespace NFairyChess {

namespace {

int CalculateKingPiecesDelta(const TBoard& board, const TMove& move) {
    int kingsDelta = 0;
    for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
        const TBoardUpdate& update = move.Updates[i];
        if (board.GetBoardPiece(update.Position).GetPieceId() == NVanillaPieces::TKingPiece::PieceId) {
            --kingsDelta;
        }
        if (TBoardPiece{update.NewBoardPiece}.GetPieceId() == NVanillaPieces::TKingPiece::PieceId) {
            ++kingsDelta;
        }
    }
    return kingsDelta;
}

int GetInitialScore(EPieceColor color) {
    return color == EPieceColor::White ?
        std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
}

int GetMaximalScore(EPieceColor color) {
    return GetInitialScore(InvertPieceColor(color));
}

int EvaluateScore(const TBoard& board) {
    TEvaluationResult eval = Evaluate(board);
    return (eval.WhiteCost - eval.BlackCost) +
        10 * (eval.WhiteAvailableMoves - eval.BlackAvailableMoves);
}

int EvaluatePieceScore(const TEvaluationResult& eval) {
    return eval.WhiteCost - eval.BlackCost;
}

int EvaluatePieceScore(const TBoard& board) {
    return EvaluatePieceScore(Evaluate(board, /* calculateAvailableMoves = */ false));
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

std::variant<TMove, EGameEnd> TMinimax::FindBestMoveOrGameEnd(const TBoard& board, EPieceColor color) {
    int score = FindBestScore(board, color, InitDepth_,
            /* alpha = */ std::numeric_limits<int>::min(),
            /* beta = */ std::numeric_limits<int>::max(),
            /* prolongatedDepth = */ 0);
    PreviousAnalyzedBoards_ = AnalyzedBoards_;

    if (score == GetMaximalScore(InvertPieceColor(color))) {
        // the enemy will win if we move!
        return EGameEnd::Defeat;
    } else {
        return BestMove_;
    }
}

int TMinimax::GetAnalyzedBoards() const {
    return AnalyzedBoards_;
}

int TMinimax::FindBestScore(const TBoard& board, EPieceColor color,
                            int depth, int alpha, int beta, int prolongatedDepth) {
    ++AnalyzedBoards_;

    //DumpBoard(board, std::cout, true);

    if ((depth <= 0 && !prolongatedDepth) || depth <= -6) {
        return EvaluateScore(board);
    }

    int bestScore = GetInitialScore(color);

    TMoveContainer moveContainer;
    GenerateMoves(moveContainer, board, color);

    // sort moves by their immediate score
    auto movesBeginIter = std::begin(moveContainer.Moves);
    auto movesEndIter = std::begin(moveContainer.Moves);
    std::advance(movesEndIter, moveContainer.MovesCount);
    std::sort(movesBeginIter, movesEndIter,
        [&board, color](const TMove& oneMove, const TMove& twoMove) {
            const int oneScore = EvaluatePieceScore(EvaluateDelta(board, oneMove));
            const int twoScore = EvaluatePieceScore(EvaluateDelta(board, twoMove));
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
        int kingsDelta = CalculateKingPiecesDelta(board, move);
        if (kingsDelta != 0) {
            // we captured the king! it's a win
            bestScore = GetMaximalScore(color);
            break;
        }

        TBoard newBoard = ApplyMove(board, move);

        const int newBoardPieceScore = EvaluatePieceScore(newBoard);
        int newProlongatedDepth = std::max(0, prolongatedDepth - 1);
        if (newBoardPieceScore != currentBoardPieceScore) {
            newProlongatedDepth = std::max(newProlongatedDepth, 1);
        }

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

    return bestScore;
}

} // namespace NFairyChess
