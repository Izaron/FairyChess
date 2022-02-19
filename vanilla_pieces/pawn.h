#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TPawnPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 1;
    static constexpr std::size_t Cost = 100;
    static constexpr std::string_view WhiteDumpStr = "♙";
    static constexpr std::string_view BlackDumpStr = "♟︎";

public:
    enum class EMoveStatus {
        NotMoved,
        MovedTwoSquares,
        Moved,
    };

public:
    auto GetMoveStatus() {
        return GetView<0, 2>();
    }

    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TPawnPiece);

} // namespace NFairyChess::NVanillaPieces
