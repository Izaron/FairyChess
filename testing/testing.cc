#include "testing.h"
#include "pretty_printer.h"

#include <gtest/gtest.h>

namespace NFairyChess {

void CheckDump(std::string_view dump, const TBoard& board) {
    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

std::unordered_set<std::string> CollectBoardDumps(const TMoveContainer& moves, const TBoard& board) {
    std::unordered_set<std::string> set;
    for (const auto& move : moves) {
        TBoard newBoard = ApplyMove(board, move);
        std::stringstream ss;
        DumpBoard(newBoard, ss);
        set.insert(ss.str());
    }
    return set;
}

} // namespace NFairyChess