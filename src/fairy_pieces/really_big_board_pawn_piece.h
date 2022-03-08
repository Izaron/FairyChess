#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TReallyBigBoardPawnPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 1;
    static constexpr std::size_t Cost = 27;
    static constexpr std::string_view WhiteDumpStr = "♙";
    static constexpr std::string_view BlackDumpStr = "♟︎";
    static constexpr std::string_view WhiteImageFile = "pawn_white.png";
    static constexpr std::string_view BlackImageFile = "pawn_black.png";

public:
    enum class EMoveStatus {
        // the pawn has not moved yet, meaning that
        // it may be able to move up to six squares forward
        NotMoved,
        // the pawn just moved two squares forward
        JustMovedTwoSquares,
        // the enemy's pawn may capture this pawn en passant
        CanBeCapturedEnPassant,
        // the pawn can move only one square forward
        Moved,
    };

public:
    auto GetMoveStatus() {
        return GetView<0, 2>();
    }

    void FillMoves(TMoveContext& moveContext);
    bool AfterMoveApply(const TBoard& /* oldBoard */, const TMove& /* move */);
};

REGISTER_PIECE(TReallyBigBoardPawnPiece);

} // namespace NFairyChess::NFairyPieces
