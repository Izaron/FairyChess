#include <gtest/gtest.h>
#include "move_generator.h"
#include "boards_assembler.h"

using namespace NFairyChess;

TEST(MoveGenerator, EmptyBoard) {
    TBoard board;
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 0);
}

TEST(MoveGenerator, VanillaBoard) {
    auto board = TBoardAssembler::AssembleVanillaBoard();
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 20);
}
