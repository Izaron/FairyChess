#include <gtest/gtest.h>
#include "atomic_pieces.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteAtomicPawn = TBoardPiece::Create<TAtomicPawnPiece>(EPieceColor::White);
const auto WhiteAtomicKnight = TBoardPiece::Create<TAtomicKnightPiece>(EPieceColor::White);
const auto WhiteAtomicRook = TBoardPiece::Create<TAtomicRookPiece>(EPieceColor::White);

const auto BlackAtomicPawn = TBoardPiece::Create<TAtomicPawnPiece>(EPieceColor::Black);
const auto BlackAtomicKnight = TBoardPiece::Create<TAtomicKnightPiece>(EPieceColor::Black);

TEST(AtomicPieces, Pawn) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteAtomicPawn)
        .SetBoardPiece({.Column = 3, .Row = 4}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 4, .Row = 5}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 5, .Row = 4}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 4, .Row = 3}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 4, .Row = 4}, BlackAtomicKnight)
        .SetBoardPiece({.Column = 5, .Row = 5}, BlackAtomicKnight)
        .SetBoardPiece({.Column = 5, .Row = 3}, BlackAtomicKnight)
        .SetBoardPiece({.Column = 3, .Row = 5}, BlackAtomicKnight)
            ;

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ♞♟︎♞  ║"
        "║   ♟︎♞♟︎  ║"
        "║   ♙♟︎♞  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 1);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║    ♟︎   ║"
        "║   ♟︎♙♟︎  ║"
        "║    ♟︎   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(AtomicPieces, Rook) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 0, .Row = 7}, WhiteAtomicRook)
        .SetBoardPiece({.Column = 1, .Row = 7}, BlackAtomicKnight)
        .SetBoardPiece({.Column = 2, .Row = 7}, BlackAtomicKnight)
        .SetBoardPiece({.Column = 0, .Row = 6}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 1, .Row = 6}, BlackAtomicPawn)
        .SetBoardPiece({.Column = 2, .Row = 6}, BlackAtomicPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║♖♞♞     ║"
        "║♟︎♟︎♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
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
        "║  ♞     ║"
        "║ ♟︎♟︎     ║"
        "║        ║"
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
        "║♟︎♟︎♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}
