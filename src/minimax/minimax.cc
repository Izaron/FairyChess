#include "minimax.h"
#include "evaluator.h"
#include "king_piece.h"
#include "pretty_printer.h"
#include "zobrist_hashing.h"

#include <limits>
#include <iostream>

namespace NFairyChess {

namespace {

bool IsRoyalPiece(TBoardPiece piece) {
    const auto* pieceInfo = TPieceRegistry::GetPieceInfo(piece.GetPieceId());
    return pieceInfo && pieceInfo->IsRoyal;
}

int CalculateRoyalPiecesDelta(const TBoard& board, const TMove& move) {
    int royalPiecesDelta = 0;
    for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
        const TBoardUpdate& update = move.Updates[i];
        if (IsRoyalPiece(board.GetBoardPiece(update.Position))) {
            --royalPiecesDelta;
        }
        if (IsRoyalPiece(update.NewBoardPiece)) {
            ++royalPiecesDelta;
        }
    }
    return royalPiecesDelta;
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
            /* prolongateDepth = */ false);
    PreviousAnalyzedBoards_ = AnalyzedBoards_;

    if (score == GetMaximalScore(InvertPieceColor(color))) {
        // the enemy will win if we move!
        // check if the enemy is attacking us, the it's a checkmate,
        // otherwise it's a stalemate
        int skipMoveScore = FindBestScore(board, InvertPieceColor(color),
                /* depth = */ 1,
                /* alpha = */ std::numeric_limits<int>::min(),
                /* beta = */ std::numeric_limits<int>::max(),
                /* prolongateDepth = */ false);
        if (skipMoveScore == GetMaximalScore(InvertPieceColor(color))) {
            return EGameEnd::Checkmate;
        } else {
            // FIXME: check for stalemate in the right way
            //return EGameEnd::Stalemate;
            return EGameEnd::Checkmate;
        }
    } else {
        uint32_t nextBoardHash = TZobristHashing::CalculateSimpleHash(ApplyMove(board, BestMove_));
        CommitedBoards_.insert(nextBoardHash);
        return BestMove_;
    }
}

int TMinimax::GetAnalyzedBoards() const {
    return AnalyzedBoards_;
}

int TMinimax::FindBestScore(const TBoard& board, EPieceColor color,
                            int depth, int alpha, int beta, bool prolongateDepth) {
    ++AnalyzedBoards_;

    if (depth != InitDepth_) {
        uint32_t boardHash = TZobristHashing::CalculateSimpleHash(board);
        if (CommitedBoards_.contains(boardHash)) {
            // we already visited this board, don't check it
            return GetMaximalScore(InvertPieceColor(color));
        }
    }

    if ((depth <= 0 && !prolongateDepth) || depth <= static_cast<int>(MinimaxProlongationDepth) * -1) {
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
        int royalPiecesDelta = CalculateRoyalPiecesDelta(board, move);
        if (royalPiecesDelta != 0) {
            // we captured a royal piece! it's a win
            bestScore = GetMaximalScore(color);
            break;
        }

        TBoard newBoard = ApplyMove(board, move);

        const int newBoardPieceScore = EvaluatePieceScore(newBoard);
        const bool newProlongateDepth = (newBoardPieceScore != currentBoardPieceScore);

        int score = FindBestScore(newBoard, InvertPieceColor(color), depth - 1,
                                  alpha, beta, newProlongateDepth);
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
