#pragma once

#include "piece_registry.h"
#include "evaluator.h"

#include "pawn_piece.h"
#include "knight_piece.h"
#include "bishop_piece.h"
#include "rook_piece.h"
#include "queen_piece.h"
#include "king_piece.h"

namespace NFairyChess::NFairyPieces {

constexpr std::size_t kAtomicPawnPieceId = 17;
constexpr std::size_t kAtomicKnightPieceId = 18;
constexpr std::size_t kAtomicBishopPieceId = 19;
constexpr std::size_t kAtomicRookPieceId = 20;
constexpr std::size_t kAtomicQueenPieceId = 21;
constexpr std::size_t kAtomicKingPieceId = 22;

template<typename T>
consteval bool IsRoyalPiece() {
    if constexpr (requires { T::IsRoyal; }) {
        return T::IsRoyal;
    }
    return false;
}

template<std::size_t AtomicPieceId, typename TUnderlyingPiece>
class TAtomicPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = AtomicPieceId;
    static constexpr std::size_t Cost = TUnderlyingPiece::Cost;
    static constexpr std::size_t IsRoyal = IsRoyalPiece<TUnderlyingPiece>();
    static constexpr std::string_view WhiteDumpStr = TUnderlyingPiece::WhiteDumpStr;
    static constexpr std::string_view BlackDumpStr = TUnderlyingPiece::BlackDumpStr;
    static constexpr std::string_view WhiteImageFile = TUnderlyingPiece::WhiteImageFile;
    static constexpr std::string_view BlackImageFile = TUnderlyingPiece::BlackImageFile;

private:
    void UnderlyingPieceFillMoves(TMoveContext& moveContext) {
        reinterpret_cast<TUnderlyingPiece*>(this)->FillMoves(moveContext);
    }

    bool IsCapturingMove(TMoveContext& moveContext, const TMove& move,
                         TBoardPosition& prevPosition, TBoardPosition& nextPosition)
    {
        if (move.UpdatesCount != 2) {
            // seems to be not a simple capture, return false
            return false;
        }

        for (std::size_t updNum = 0; updNum < 2; ++updNum) {
            const TBoardUpdate& boardUpdate = move.Updates[updNum];

            TBoardPiece prevBoardPiece = moveContext.Board.GetBoardPiece(boardUpdate.Position);
            TBoardPiece nextBoardPiece = boardUpdate.NewBoardPiece;

            if (!prevBoardPiece.IsEmpty() && !nextBoardPiece.IsEmpty()) {
                // we captured an enemy piece
                prevPosition = move.Updates[1 - updNum].Position;
                nextPosition = move.Updates[updNum].Position;
                return true;
            }
        }

        return false;
    }

    void MakeAtomicBlast(TMoveContext& moveContext, TMove& move,
                         TBoardPosition& prevPosition, TBoardPosition& nextPosition)
    {
        // consider all 8 neighboring cells
        for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
            for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
                if (deltaCol == 0 && deltaRow == 0) {
                    continue;
                }
                TBoardPosition boardPosition = nextPosition;

                // check if the position is outside the board
                if (!moveContext.Board.ShiftPosition(boardPosition, {.Column = deltaCol, .Row = deltaRow})) {
                    continue;
                }

                // check if position is same as piece's previous position
                if (boardPosition == prevPosition) {
                    continue;
                }

                // check if the board piece is empty or is an atomic pawn
                TBoardPiece boardPiece = moveContext.Board.GetBoardPiece(boardPosition);
                if (boardPiece.IsEmpty() || boardPiece.GetPieceId() == kAtomicPawnPieceId) {
                    continue;
                }

                // the piece is removed by the blast!
                move.Updates[move.UpdatesCount++] = {boardPosition, EmptyBoardPiece()};
            }
        }

        // consider this cell and remove if this isn't an atomic pawn
        if (PieceId != kAtomicPawnPieceId) {
            std::size_t updIndex = 0;
            while (move.Updates[updIndex].Position != nextPosition) {
                ++updIndex;
            }
            move.Updates[updIndex].NewBoardPiece = EmptyBoardPiece();
        }
    }

    void FixPieceIds(TMove& move) {
        for (std::size_t updNum = 0; updNum < move.UpdatesCount; ++updNum) {
            TBoardPiece& boardPiece = move.Updates[updNum].NewBoardPiece;
            if (boardPiece.IsEmpty()) {
                continue;
            }

            switch (boardPiece.GetPieceId()) {
                case NVanillaPieces::TPawnPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicPawnPieceId);
                    break;
                }
                case NVanillaPieces::TKnightPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicKnightPieceId);
                    break;
                }
                case NVanillaPieces::TBishopPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicBishopPieceId);
                    break;
                }
                case NVanillaPieces::TRookPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicRookPieceId);
                    break;
                }
                case NVanillaPieces::TQueenPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicQueenPieceId);
                    break;
                }
                case NVanillaPieces::TKingPiece::PieceId: {
                    boardPiece.SetPieceId(kAtomicKingPieceId);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

public:
    void FillMoves(TMoveContext& moveContext) {
        TMoveContainer* moveContainer = dynamic_cast<TMoveContainer*>(&moveContext.Moves);
        if (!moveContainer) {
            // this is a dummy container, do nothing
            UnderlyingPieceFillMoves(moveContext);
            return;
        }

        std::size_t beforeMovesCount = moveContainer->MovesCount;
        UnderlyingPieceFillMoves(moveContext);
        std::size_t afterMovesCount = moveContainer->MovesCount;

        const EPieceColor color = moveContext.Board.GetBoardPiece(moveContext.Position).GetColor();

        for (std::size_t moveIndex = beforeMovesCount; moveIndex < afterMovesCount; ++moveIndex) {
            TMove& move = moveContainer->Moves[moveIndex];

            TBoardPosition prevPosition, nextPosition;
            if (IsCapturingMove(moveContext, move, prevPosition, nextPosition)) {
                MakeAtomicBlast(moveContext, move, prevPosition, nextPosition);
            }
            FixPieceIds(move);
        }
    }
};

using TAtomicPawnPiece = TAtomicPiece<kAtomicPawnPieceId, NVanillaPieces::TPawnPiece>;
using TAtomicKnightPiece = TAtomicPiece<kAtomicKnightPieceId, NVanillaPieces::TKnightPiece>;
using TAtomicBishopPiece = TAtomicPiece<kAtomicBishopPieceId, NVanillaPieces::TBishopPiece>;
using TAtomicRookPiece = TAtomicPiece<kAtomicRookPieceId, NVanillaPieces::TRookPiece>;
using TAtomicQueenPiece = TAtomicPiece<kAtomicQueenPieceId, NVanillaPieces::TQueenPiece>;
using TAtomicKingPiece = TAtomicPiece<kAtomicKingPieceId, NVanillaPieces::TKingPiece>;

REGISTER_PIECE(TAtomicPawnPiece);
REGISTER_PIECE(TAtomicKnightPiece);
REGISTER_PIECE(TAtomicBishopPiece);
REGISTER_PIECE(TAtomicRookPiece);
REGISTER_PIECE(TAtomicQueenPiece);
REGISTER_PIECE(TAtomicKingPiece);

} // namespace NFairyChess::NVanillaPieces
