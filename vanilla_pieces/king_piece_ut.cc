#include <gtest/gtest.h>
#include "king_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteKing = TBoardPiece::Create<TKingPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(King, AllMoves) {
    auto board = TBoard{}.SetBoardPiece({.Column = 3, .Row = 3}, WhiteKing);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ♔    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 8);
}

TEST(King, Capturing) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteKing)
        .SetBoardPiece({.Column = 3, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 4}, BlackDummy)
        .SetBoardPiece({.Column = 4, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 2}, BlackDummy)
        .SetBoardPiece({.Column = 3, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 2}, BlackDummy)
        .SetBoardPiece({.Column = 2, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 4}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║  ●○●   ║"
        "║  ○♔○   ║"
        "║  ●○●   ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    auto moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 4);
}
