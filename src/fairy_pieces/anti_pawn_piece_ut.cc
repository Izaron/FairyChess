#include <gtest/gtest.h>
#include "anti_pawn_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteAntiPawn = TBoardPiece::Create<TAntiPawnPiece>(EPieceColor::White);

TEST(Pawn, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 2, .Row = 1}, WhiteAntiPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ♙     ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 4);
}

// FIXME: add more tests
