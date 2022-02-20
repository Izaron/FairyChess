#pragma once

#include "board.h"
#include "move_generator.h"

#include <unordered_set>

namespace NFairyChess {

void CheckDump(std::string_view dump, const TBoard& board);
std::unordered_set<std::string> CollectBoardDumps(const TMoveContainer& moves, const TBoard& board);

} // namespace NFairyChess
