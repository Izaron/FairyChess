#include <gtest/gtest.h>
#include "board_piece.h"

using namespace NFairyChess;

class TTestPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 999;
    static constexpr std::size_t Cost = 999;

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

    TBoardPiece bp = TBoardPiece::CreateFromExisting(EPieceColor::Black, testPiece);
    EXPECT_EQ(bp.GetColor(), EPieceColor::Black);
    EXPECT_EQ(bp.GetPieceId(), 999);

    TPieceOrEmpty<TTestPiece> pieceOrEmpty = bp.GetPieceOrEmpty<TTestPiece>();
    EXPECT_EQ(pieceOrEmpty.IsEmpty(), false);
    TTestPiece unpackedPiece = pieceOrEmpty.GetPiece();
    EXPECT_EQ(unpackedPiece.GetTestValue().GetValue(), 63);
}
