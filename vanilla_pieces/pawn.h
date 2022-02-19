#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TPawnPiece : public TPiece {
public:
    static constexpr std::size_t UniqueId = 1;
    static constexpr std::size_t Cost = 100;

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

    void FillMoves() {
    }
};

REGISTER_FIGURE(TPawnPiece);

} // namespace NFairyChess::NVanillaPieces
