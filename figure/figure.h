#pragma once

#include <cstdint>

#include "bit_storage.h"

namespace NFairyChess {

using TStorageType = uint32_t;

// Storage layout is defined by concrete figures
class TFigure : public TBitStorage<TStorageType> {
public:
};

template<typename T>
concept TFigureType = std::is_base_of_v<TFigure, T>;

} // namespace NFairyChess
