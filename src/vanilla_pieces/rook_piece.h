#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TRookPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 4;
    static constexpr std::size_t Cost = 500;
    static constexpr std::string_view WhiteDumpStr = "♖";
    static constexpr std::string_view BlackDumpStr = "♜";
    static constexpr std::string_view WhiteImageFile = "rook_white.png";
    static constexpr std::string_view BlackImageFile = "rook_black.png";

public:
    enum class EMoveStatus {
        // the rook has not moved yet, meaning that
        // it may be able to castle
        NotMoved,
        // the rook has moved
        Moved,
    };

public:
    auto GetMoveStatus() {
        return GetView<0, 1>();
    }

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TRookPiece);

} // namespace NFairyChess::NVanillaPieces
