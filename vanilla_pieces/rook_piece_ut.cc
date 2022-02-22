#include <gtest/gtest.h>
#include "rook_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteRook = TBoardPiece::Create<TRookPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::Black);

TEST(Rook, AllMoves) {
    auto board = TBoard{}.SetBoardPiece({.Column = 3, .Row = 3}, WhiteRook);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ♖    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 14);
}

TEST(Rook, Capturing) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteRook)
        .SetBoardPiece({.Column = 5, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 5}, BlackDummy)
        .SetBoardPiece({.Column = 1, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, BlackDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ●    ║"
        "║        ║"
        "║ ○ ♖ ○  ║"
        "║        ║"
        "║   ●    ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 6);
}
