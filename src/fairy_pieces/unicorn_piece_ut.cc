#include <gtest/gtest.h>
#include "unicorn_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteUnicorn = TBoardPiece::Create<TUnicornPiece>(EPieceColor::White);

TEST(Unicorn, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteUnicorn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    U   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 16);
}
