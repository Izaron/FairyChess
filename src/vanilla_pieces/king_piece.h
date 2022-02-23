#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TKingPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 6;
    static constexpr std::size_t Cost = 20000;
    static constexpr std::string_view WhiteDumpStr = "♔";
    static constexpr std::string_view BlackDumpStr = "♚";
    static constexpr std::string_view WhiteImageFile = "king_white.png";
    static constexpr std::string_view BlackImageFile = "king_black.png";

public:
    enum class EMoveStatus {
        // the king has not moved yet, meaning that
        // it may be able to castle
        NotMoved,
        // the king has moved
        Moved,
    };

public:
    auto GetMoveStatus() {
        return GetView<0, 1>();
    }

    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TKingPiece);

} // namespace NFairyChess::NVanillaPieces
