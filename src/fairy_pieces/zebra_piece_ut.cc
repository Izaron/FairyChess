#include <gtest/gtest.h>
#include "zebra_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteZebra = TBoardPiece::Create<TZebraPiece>(EPieceColor::White);

TEST(Zebra, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteZebra);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    Z   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 8);
}
