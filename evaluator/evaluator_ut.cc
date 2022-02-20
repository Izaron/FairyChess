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
    EXPECT_EQ(r.WhiteCost, 1400);
    EXPECT_EQ(r.BlackCost, 1400);
}
