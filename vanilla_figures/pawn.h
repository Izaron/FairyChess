#pragma once

#include "figure.h"

namespace NFairyChess::NVanillaFigures {

class TPawnFigure : public TFigure {
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
};

} // namespace NFairyChess::NVanillaFigures
