#include <gtest/gtest.h>
#include "pawn.h"
#include "pretty_printer.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;

const auto WhitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);
const auto BlackPawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::Black);

static void CheckDump(std::string_view dump, const TBoard& board) {
    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(Pawn, SingleWhitePiece) {
    auto board1 = TBoard{}.SetBoardPiece({.Column = 1, .Row = 1}, WhitePawn);

    // check initial position
    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    // find moves
    TMoveContainer moves = GenerateMoves(board1, EPieceColor::White);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check dump
    auto board2 = ApplyMove(board1, moves[0]);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

// Checking that black pieces have mirroring behaviour
TEST(Pawn, SingleBlackPiece) {
    auto board1 = TBoard{}.SetBoardPiece({.Column = 6, .Row = 6}, BlackPawn);

    // check initial position
    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║      ♟︎ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    // find moves
    TMoveContainer moves = GenerateMoves(board1, EPieceColor::Black);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check dump
    auto board2 = ApplyMove(board1, moves[0]);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║      ♟︎ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

TEST(Pawn, BlockedPiece) {
    // Check that piece can't go forward if there is another piece there
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 1}, WhitePawn)
        .SetBoardPiece({.Column = 1, .Row = 2}, WhitePawn);

    // check initial position
    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    // check that there is only one move possible
    TMoveContainer moves = GenerateMoves(board1, EPieceColor::White);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check dump
    auto board2 = ApplyMove(board1, moves[0]);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}
