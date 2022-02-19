#include <gtest/gtest.h>
#include "board.h"
#include "boards_assembler.h"

using namespace NFairyChess;

TEST(BoardTest, TestIterator) {
    const TBoard board = TBoardAssembler::AssembleVanillaBoard();
    std::size_t counter = 0;
    for (TBoardPiece bp : board) {
        ++counter;
    }
    EXPECT_EQ(counter, 16);
}
