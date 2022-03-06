#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

// This class is almost copy-pasted from TPawnPiece,
class TAntiPawnPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 8;
    static constexpr std::size_t Cost = 100;
    static constexpr std::string_view WhiteDumpStr = "♙";
    static constexpr std::string_view BlackDumpStr = "♟︎";
    static constexpr std::string_view WhiteImageFile = "pawn_rotated_white.png";
    static constexpr std::string_view BlackImageFile = "pawn_rotated_black.png";

public:
    enum class EMoveStatus {
        // the pawn has not moved yet, meaning that
        // it may be able to move two squares forward
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
    bool AfterMoveApply();
};

REGISTER_PIECE(TAntiPawnPiece);

} // namespace NFairyChess::NVanillaPieces
