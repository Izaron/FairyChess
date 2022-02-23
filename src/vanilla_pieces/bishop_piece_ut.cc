#include <gtest/gtest.h>
#include "bishop_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteBishop = TBoardPiece::Create<TBishopPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(Bishop, AllMoves) {
    auto board = TBoard{}.SetBoardPiece({.Column = 3, .Row = 3}, WhiteBishop);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ♗    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 13);
}

TEST(Bishop, Capturing) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteBishop)
        .SetBoardPiece({.Column = 4, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 4}, BlackDummy)
        .SetBoardPiece({.Column = 2, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 2}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ● ○   ║"
        "║   ♗    ║"
        "║  ○ ●   ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 2);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ♗ ○   ║"
        "║        ║"
        "║  ○ ●   ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ● ○   ║"
        "║        ║"
        "║  ○ ♗   ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}
