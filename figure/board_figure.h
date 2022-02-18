#pragma once

#include "figure.h"

namespace NFairyChess {

// Storage layout:
// [0] - color
// [1..11] - figure type
// [12...] - figure's storage
class TBoardFigure : public TBitStorage<TStorageType> {
public:
    enum class EColor {
        White,
        Black,
    };

public:
    EColor GetColor() {
        return GetView<0, 1>().GetValue<EColor>();
    }

    std::size_t GetFigureType() {
        return GetView<1, 11>().GetValue<std::size_t>();
    }

    template<TFigureType T>
    T GetFigure() {
        return T{GetView<12>().GetValue()};
    }
};

} // namespace NFairyChess
