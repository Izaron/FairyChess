#include <gtest/gtest.h>
#include "king_piece.h"
#include "rook_piece.h"
#include "dummy_piece.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteKing = TBoardPiece::Create<TKingPiece>(EPieceColor::White);
const auto WhiteRook = TBoardPiece::Create<TRookPiece>(EPieceColor::White);
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
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 8);
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
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 4);
}

TEST(King, ShortCastling) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 0}, WhiteKing)
        .SetBoardPiece({.Column = 7, .Row = 0}, WhiteRook)
        .SetBoardPiece({.Column = 3, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 7, .Row = 1}, WhiteDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ○○○○○║"
        "║   ○♔  ♖║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 4);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   ○○○○○║"
        "║   ○♔ ♖ ║"
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
        "║   ○○○○○║"
        "║   ○♔♖  ║"
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
        "║   ○○○○○║"
        "║   ○ ♔ ♖║"
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
        "║   ○○○○○║"
        "║   ○ ♖♔ ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(King, LongCastling) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 0}, WhiteKing)
        .SetBoardPiece({.Column = 0, .Row = 0}, WhiteRook)
        .SetBoardPiece({.Column = 5, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 0, .Row = 1}, WhiteDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║○○○○○○  ║"
        "║♖   ♔○  ║"
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
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║○○○○○○  ║"
        "║♖  ♔ ○  ║"
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
        "║○○○○○○  ║"
        "║ ♖  ♔○  ║"
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
        "║○○○○○○  ║"
        "║  ♖ ♔○  ║"
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
        "║○○○○○○  ║"
        "║   ♖♔○  ║"
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
        "║○○○○○○  ║"
        "║  ♔♖ ○  ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}
