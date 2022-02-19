#pragma once

#include "piece.h"
#include "piece_or_empty.h"

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
        return TBoardPiece(color, /* pieceId = */ Type::PieceId,
                           /* pieceStorage = */ piece.GetView().GetValue());
    }

    template<TPieceType Type>
    static TBoardPiece Create(EPieceColor color) {
        return TBoardPiece(color, /* pieceId = */ Type::PieceId, /* pieceStorage = */ 0);
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
    TPieceOrEmpty<T> GetPieceOrEmpty() {
        if (GetPieceId() == T::PieceId) {
            return TPieceOrEmpty<T>{GetView<11>().GetValue()};
        }
        return {};
    }

    bool IsEmpty() {
        return GetPieceId() == 0;
    }

private:
    TBoardPiece(EPieceColor color, std::size_t pieceId, TStorageType pieceStorage = 0);
};

} // namespace NFairyChess
