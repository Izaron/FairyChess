#include <gtest/gtest.h>
#include "princess_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhitePrincess = TBoardPiece::Create<TPrincessPiece>(EPieceColor::White);

TEST(Princess, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhitePrincess);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    P   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 21);
}
