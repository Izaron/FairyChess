#pragma once

#include "piece.h"

namespace NFairyChess {

enum class EPieceColor {
    White,
    Black,
};

// Storage layout:
// [0] - color
// [1..11] - piece type
// [12...] - piece storage
class TBoardPiece : public TBitStorage<TStorageType> {
public:
    template<TPieceType Type>
    static TBoardPiece Create(EPieceColor color) {
        return TBoardPiece(color, /* type = */ 0, /* pieceStorage = */ 0);
    }

public:
    TBoardPiece(); // creates an empty piece

    EPieceColor GetColor() {
        return GetView<0, 1>().GetValue<EPieceColor>();
    }

    std::size_t GetType() {
        return GetView<1, 11>().GetValue<std::size_t>();
    }

    template<TPieceType T>
    T GetPiece() {
        return T{GetView<12>().GetValue()};
    }

private:
    TBoardPiece(EPieceColor color, std::size_t type, TStorageType pieceStorage = 0);
};

} // namespace NFairyChess
