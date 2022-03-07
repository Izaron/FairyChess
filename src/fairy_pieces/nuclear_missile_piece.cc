#include "nuclear_missile_piece.h"
#include "king_piece.h"
#include "pawn_piece.h"

namespace NFairyChess::NFairyPieces {

using enum TNuclearMissilePiece::EEscalationStatus;

namespace {

void AddSimpleMoves(TMoveContext& ctx) {
    // add simple moves (same as for king)
    TBoardPiece boardPiece = ctx.Board.GetBoardPiece(ctx.Position);
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(ctx, boardPiece, EMoveType::Leaper,
                             {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

void TryAddNuclearBlastMove(TMoveContext& ctx, int col, int row) {
    const auto& board = ctx.Board;
    TMoveBuilder moveBuilder;

    // remove every non-king piece in 3x3 region
    std::size_t removedPiecesCount = 0;
    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            TBoardPosition pos{.Column = col, .Row = row};
            if (!board.ShiftPosition(pos, {.Column = deltaCol, .Row = deltaRow})) {
                continue;
            }

            TBoardPiece boardPiece = board.GetBoardPiece(pos);
            if (boardPiece.IsEmpty() ||
                    boardPiece.GetPieceId() == NVanillaPieces::TKingPiece::PieceId ||
                    boardPiece.GetPieceId() == TNuclearMissilePiece::PieceId)
            {
                continue;
            }

            moveBuilder.RemoveBoardPiece(pos);
            ++removedPiecesCount;
        }
    }

    if (removedPiecesCount > 0) {
        // remove the nuclear missile piece itself
        moveBuilder.RemoveBoardPiece(ctx.Position);

        // add the move
        ctx.Moves.Add(moveBuilder.Build());
    }
}

void AddNuclearBlastMoves(TMoveContext& ctx) {
    // add nuclear blast on every board square
    const auto& board = ctx.Board;
    for (int col = 0; col < board.GetColumns(); ++col) {
        for (int row = 0; row < board.GetRows(); ++row) {
            TryAddNuclearBlastMove(ctx, col, row);
        }
    }
}

} // namespace

void TNuclearMissilePiece::FillMoves(TMoveContext& ctx) {
    AddSimpleMoves(ctx);

    const EEscalationStatus status = GetEscalationStatus().GetValue<EEscalationStatus>();
    if (status == EEscalationStatus::Escalated) {
        AddNuclearBlastMoves(ctx);
    }
}

bool TNuclearMissilePiece::AfterMoveApply(const TBoard& oldBoard, const TMove& move) {
    auto escalationStatus = GetEscalationStatus();
    if (escalationStatus.GetValue<EEscalationStatus>() == EEscalationStatus::NotEscalated) {
        std::array<int, 5> piecesBalance{};

        for (std::size_t i = 0; i < move.UpdatesCount; ++i) {
            const TBoardUpdate& upd = move.Updates[i];

            // add new board piece to the balance
            {
                const std::size_t pieceId = TBoardPiece{upd.NewBoardPiece}.GetPieceId();
                if (pieceId >= 2 && pieceId <= 6) {
                    ++piecesBalance[pieceId - 2];
                }
            }

            // substract old board from the balance
            {
                const std::size_t pieceId = oldBoard.GetBoardPiece(upd.Position).GetPieceId();
                if (pieceId >= 2 && pieceId <= 6) {
                    --piecesBalance[pieceId - 2];
                }
            }
        }

        bool pieceCaptured = false;
        for (int balance : piecesBalance) {
            if (balance != 0) {
                pieceCaptured = true;
                break;
            }
        }

        if (pieceCaptured) {
            // escalate!
            GetEscalationStatus().SetValue(EEscalationStatus::Escalated);
            return true;
        }
    }
    return false;
}

} // namespace NFairyChess::NFairyPieces
