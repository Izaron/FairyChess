#include <gtest/gtest.h>
#include "knight_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteKnight = TBoardPiece::Create<TKnightPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(Knight, AllMoves) {
    auto board = TBoard{}.SetBoardPiece({.Column = 3, .Row = 3}, WhiteKnight);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ♘    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 8);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║     ♘  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║     ♘  ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    ♘   ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ♘     ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♘      ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♘      ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ♘     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║    ♘   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(Knight, Capturing) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteKnight)
        .SetBoardPiece({.Column = 5, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 5}, BlackDummy)
        .SetBoardPiece({.Column = 2, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 4}, BlackDummy)
        .SetBoardPiece({.Column = 1, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 1}, BlackDummy)
        .SetBoardPiece({.Column = 4, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 2}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○ ●   ║"
        "║ ●   ○  ║"
        "║   ♘    ║"
        "║ ○   ●  ║"
        "║  ● ○   ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 4);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○ ♘   ║"
        "║ ●   ○  ║"
        "║        ║"
        "║ ○   ●  ║"
        "║  ● ○   ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○ ●   ║"
        "║ ●   ○  ║"
        "║        ║"
        "║ ○   ♘  ║"
        "║  ● ○   ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○ ●   ║"
        "║ ●   ○  ║"
        "║        ║"
        "║ ○   ●  ║"
        "║  ♘ ○   ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○ ●   ║"
        "║ ♘   ○  ║"
        "║        ║"
        "║ ○   ●  ║"
        "║  ● ○   ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}
