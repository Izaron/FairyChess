#pragma once

#include <cstdint>
#include <string_view>

#include "bit_storage.h"

namespace NFairyChess {

using TStorageType = uint32_t;

// Storage layout is defined by concrete pieces
class TPiece : public TBitStorage<TStorageType> {};

template<typename T>
concept TPieceType = std::is_base_of_v<TPiece, T>;

} // namespace NFairyChess
