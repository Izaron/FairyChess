#include <gtest/gtest.h>
#include "champion_piece.h"
#include "dummy_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteChampion = TBoardPiece::Create<TChampionPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);

TEST(Champion, MovesCount) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteChampion);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    C   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 12);
}

TEST(Champion, MovesPosition) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 3}, WhiteChampion)
        .SetBoardPiece({.Column = 3, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 3}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 5}, WhiteDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ○   ○ ║"
        "║   ○○○  ║"
        "║   ○C○  ║"
        "║   ○○○  ║"
        "║  ○   ○ ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 0);
}
