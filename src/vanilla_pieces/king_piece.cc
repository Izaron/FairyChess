#include "king_piece.h"
#include "rook_piece.h"

namespace NFairyChess::NVanillaPieces {

namespace {

bool HasNotMovedRook(TBoardPiece boardPiece, EPieceColor color) {
    if (auto rookOrEmpty = boardPiece.GetPieceOrEmpty<TRookPiece>(); !rookOrEmpty.IsEmpty()) {
        TRookPiece rookPiece = rookOrEmpty.GetPiece();
        if (boardPiece.GetColor() == color) {
            const TRookPiece::EMoveStatus moveStatus = rookPiece.GetMoveStatus().GetValue<TRookPiece::EMoveStatus>();
            return moveStatus == TRookPiece::EMoveStatus::NotMoved;
        }
    }
    return false;
}

void AddCastlingMove(TMoveContext& ctx, TBoardPiece kingPiece, int direction, TBoardPosition prevRookPos) {
    // previous king position
    TBoardPosition prevKingPos = ctx.Position;

    // new rook position and rook piece
    TBoardPosition rookPos = ctx.Position;
    ctx.Board.ShiftPosition(rookPos, {.Column = direction, .Row = 0});
    TRookPiece newRookPiece;
    newRookPiece.GetMoveStatus().SetValue(TRookPiece::EMoveStatus::Moved);

    // new king position
    TBoardPosition kingPos = rookPos;
    ctx.Board.ShiftPosition(kingPos, {.Column = direction, .Row = 0});

    // add the move
    ctx.Moves.Add(
        TMoveBuilder{}
            .RemoveBoardPiece(prevKingPos)
            .RemoveBoardPiece(prevRookPos)
            .SetBoardPiece(rookPos, TBoardPiece::CreateFromExisting(kingPiece.GetColor(), newRookPiece))
            .SetBoardPiece(kingPos, kingPiece)
            .Build()
    );
}

void TryAddCastlingMoves(TMoveContext& ctx, TBoardPiece kingPiece) {
    // search for non-moved rook in both directions
    for (int dir : {-1, 1}) {
        TBoardPosition pos = ctx.Position;
        while (ctx.Board.ShiftPosition(pos, {.Column = dir, .Row = 0})) {
            TBoardPiece boardPiece = ctx.Board.GetBoardPiece(pos);

            // there is a non-moved rook of our color! check if it hasn't moved yet
            if (HasNotMovedRook(boardPiece, kingPiece.GetColor())) {
                AddCastlingMove(ctx, kingPiece, dir, pos);
            }

            // there is another piece on the way! can't make castles
            if (!boardPiece.IsEmpty()) {
                break;
            }
        }
    }
}

} // namespace

void TKingPiece::FillMoves(TMoveContext& moveContext) {
    // mark the king as "moved"
    TKingPiece newKingPiece = *this;
    auto moveStatus = newKingPiece.GetMoveStatus();

    bool tryMakeCastlingMoves = false;
    if (moveStatus.GetValue<EMoveStatus>() != EMoveStatus::Moved) {
        tryMakeCastlingMoves = true;
        moveStatus.SetValue(EMoveStatus::Moved);
    }

    const EPieceColor color = moveContext.Board.GetBoardPiece(moveContext.Position).GetColor();
    TBoardPiece newBoardPiece = TBoardPiece::CreateFromExisting(color, newKingPiece);

    // try add castling move
    if (tryMakeCastlingMoves) {
        TryAddCastlingMoves(moveContext, newBoardPiece);
    }

    for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            if (deltaCol == 0 && deltaRow == 0) {
                continue;
            }
            AddStandardMoves(moveContext, newBoardPiece, EMoveType::Leaper,
                             {.Column = deltaCol, .Row = deltaRow});
        }
    }
}

} // namespace NFairyChess::NVanillaPieces
