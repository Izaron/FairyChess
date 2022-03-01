#include <gtest/gtest.h>
#include "mann_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteMann = TBoardPiece::Create<TMannPiece>(EPieceColor::White);

TEST(Mann, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteMann);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    M   ║"
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
