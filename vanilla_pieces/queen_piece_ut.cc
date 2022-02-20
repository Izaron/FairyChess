#include <gtest/gtest.h>
#include "queen_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(Queen, AllMoves) {
    auto board = TBoard{}.SetBoardPiece({.Column = 3, .Row = 3}, WhiteQueen);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ♕    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 27);
}

TEST(Queen, Capturing) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteQueen)
        .SetBoardPiece({.Column = 3, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 5}, BlackDummy)
        .SetBoardPiece({.Column = 5, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 1}, BlackDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 1}, BlackDummy)
        .SetBoardPiece({.Column = 1, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 5}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║ ● ○ ●  ║"
        "║        ║"
        "║ ○ ♕ ○  ║"
        "║        ║"
        "║ ● ○ ●  ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 12);
}
