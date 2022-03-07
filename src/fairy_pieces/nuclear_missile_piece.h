#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TNuclearMissilePiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 23;
    static constexpr std::size_t Cost = 500;
    static constexpr std::string_view WhiteDumpStr = "N";
    static constexpr std::string_view BlackDumpStr = "n";
    static constexpr std::string_view WhiteImageFile = "radioactive_white.png";
    static constexpr std::string_view BlackImageFile = "radioactive_black.png";

public:
    enum class EEscalationStatus {
        // we can't blow the missile now, because there are
        // no non-pawn pieces captured
        NotEscalated,
        // a non-pawn piece is captured, we can blow the missile
        Escalated,
    };

public:
    auto GetEscalationStatus() {
        return GetView<0, 1>();
    }

    void FillMoves(TMoveContext& moveContext);
    bool AfterMoveApply(const TBoard& oldBoard, const TMove& move);
};

REGISTER_PIECE(TNuclearMissilePiece);

} // namespace NFairyChess::NFairyPieces
