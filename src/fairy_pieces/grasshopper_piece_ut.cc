#include <gtest/gtest.h>
#include "grasshopper_piece.h"
#include "dummy_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;
using namespace NFairyChess::NVanillaPieces;

const auto WhiteGrasshopper = TBoardPiece::Create<TGrasshopperPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(Grasshopper, Smoke) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteGrasshopper)
        .SetBoardPiece({.Column = 4, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 6}, BlackDummy)
        .SetBoardPiece({.Column = 1, .Row = 5}, BlackDummy)
        .SetBoardPiece({.Column = 0, .Row = 6}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║●     ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║   G○○  ║"
        "║  ○     ║"
        "║   ○    ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 5);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║●     ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║    ○○  ║"
        "║  ○     ║"
        "║   ○    ║"
        "║   G    ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║●     ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║    ○○  ║"
        "║  ○     ║"
        "║ G ○    ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║G     ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║    ○○  ║"
        "║  ○     ║"
        "║   ○    ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║●  G  ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║    ○○  ║"
        "║  ○     ║"
        "║   ○    ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║       G║"
        "║●     ● ║"
        "║ ● ○    ║"
        "║        ║"
        "║    ○○  ║"
        "║  ○     ║"
        "║   ○    ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}
