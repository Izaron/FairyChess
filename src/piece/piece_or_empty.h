#pragma once

#include "piece.h"

namespace NFairyChess {

template<TPieceType T>
class TPieceOrEmpty : public TBitStorage<TStorageType> {
public:
    TPieceOrEmpty() {
        GetEmptyFlag().SetValue(1);
    }

    TPieceOrEmpty(TStorageType storage) {
        GetEmptyFlag().SetValue(0);
        GetView<1>().SetValue(storage);
    }

    bool IsEmpty() {
        return GetEmptyFlag().GetValue();
    }

    T GetPiece() {
        return T{GetView<1>().GetValue()};
    }

private:
    auto GetEmptyFlag() {
        return GetView<0, 1>();
    }
};

} // namespace NFairyChess
