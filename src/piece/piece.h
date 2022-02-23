#pragma once

#include <cstdint>
#include <string_view>

#include "bit_storage.h"

namespace NFairyChess {

using TStorageType = uint32_t;

// Storage layout is defined by concrete pieces
class TPiece : public TBitStorage<TStorageType> {};

template<typename T>
concept TPieceType = requires {
    std::is_base_of_v<TPiece, T>;
    std::is_same_v<std::size_t, decltype(T::PieceId)>;
    std::is_same_v<std::size_t, decltype(T::Cost)>;
};

} // namespace NFairyChess
