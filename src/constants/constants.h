#pragma once

#include <cstddef>

namespace NFairyChess {

inline constexpr std::size_t BoardPiecesMaxCount = 64;

inline constexpr std::size_t MinimaxDepth = 4;
inline constexpr std::size_t MinimaxProlongationDepth = 6;

inline constexpr std::size_t MaximalBoardUpdatesInMoveCount = 10;
inline constexpr std::size_t MaximalMovesCount = 128;

} // namespace NFairyChess
