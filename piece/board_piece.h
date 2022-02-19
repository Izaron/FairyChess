#pragma once

#include "piece.h"

namespace NFairyChess {

// Storage layout:
// [0] - color
// [1..11] - piece type
// [12...] - piece storage
class TBoardPiece : public TBitStorage<TStorageType> {
public:
    enum class EColor {
        White,
        Black,
    };

public:
    EColor GetColor() {
        return GetView<0, 1>().GetValue<EColor>();
    }

    std::size_t GetPieceType() {
        return GetView<1, 11>().GetValue<std::size_t>();
    }

    template<TPieceType T>
    T GetPiece() {
        return T{GetView<12>().GetValue()};
    }
};

} // namespace NFairyChess
