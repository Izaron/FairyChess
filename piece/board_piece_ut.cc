#include <gtest/gtest.h>
#include "board_piece.h"

using namespace NFairyChess;

class TTestPiece : public TPiece {
public:
    static constexpr std::size_t UniqueId = 999;

public:
    auto GetTestValue() {
        return GetView();
    }
};

TEST(BoardPieceTest, EmptyPiece) {
    TBoardPiece bp;
    EXPECT_EQ(bp.GetColor(), EPieceColor::White);
    EXPECT_EQ(bp.GetPieceId(), 0);
}

TEST(BoardPieceTest, PiecePackAndUnpack) {
    TTestPiece testPiece;
    testPiece.GetTestValue().SetValue(63);

    auto bp = TBoardPiece::CreateFromExisting(EPieceColor::Black, testPiece);
    EXPECT_EQ(bp.GetColor(), EPieceColor::Black);
    EXPECT_EQ(bp.GetPieceId(), 999);

    auto unpackedPiece = bp.GetPiece<TTestPiece>();
    EXPECT_EQ(unpackedPiece.GetTestValue().GetValue(), 63);
}
