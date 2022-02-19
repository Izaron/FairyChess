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
    static TBoardPiece CreateFromExisting(EPieceColor color, Type piece) {
        return TBoardPiece(color, /* pieceId = */ Type::UniqueId,
                           /* pieceStorage = */ piece.GetView().GetValue());
    }

    template<TPieceType Type>
    static TBoardPiece Create(EPieceColor color) {
        return TBoardPiece(color, /* pieceId = */ Type::UniqueId, /* pieceStorage = */ 0);
    }

public:
    TBoardPiece(); // creates an empty piece

    EPieceColor GetColor() {
        return GetView<0, 1>().GetValue<EPieceColor>();
    }

    std::size_t GetPieceId() {
        return GetView<1, 11>().GetValue<std::size_t>();
    }

    template<TPieceType T>
    T GetPiece() {
        return T{GetView<11>().GetValue()};
    }

private:
    TBoardPiece(EPieceColor color, std::size_t pieceId, TStorageType pieceStorage = 0);
};

} // namespace NFairyChess
