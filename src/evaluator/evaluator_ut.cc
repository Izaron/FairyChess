#include <gtest/gtest.h>
#include "evaluator.h"
#include "boards_assembler.h"

using namespace NFairyChess;

TEST(EvaluatorTest, EmptyBoard) {
    const TEvaluationResult r = Evaluate(TBoard());
    EXPECT_EQ(r.WhiteCost, 0);
    EXPECT_EQ(r.BlackCost, 0);
}

TEST(EvaluatorTest, VanillaBoard) {
    const TBoard board = TBoardAssembler::AssembleVanillaBoard();
    const TEvaluationResult r = Evaluate(board);
    EXPECT_EQ(r.WhiteCost, 23900);
    EXPECT_EQ(r.BlackCost, 23900);
    EXPECT_EQ(r.WhiteAvailableMoves, 20);
    EXPECT_EQ(r.BlackAvailableMoves, 20);
}
