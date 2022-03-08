#include <gtest/gtest.h>
#include "dragon_piece.h"
#include "dummy_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteDragon = TBoardPiece::Create<TDragonPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);

TEST(Dragon, MovesCount) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 16 * 16) {
        auto board = TBoard{/* columns = */ 16, /* rows = */ 16}
            .SetBoardPiece({.Column = 8, .Row = 7}, WhiteDragon);

        // check initial position
        std::string_view dump =
            "╔════════════════╗"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║        D       ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "╚════════════════╝";
        CheckDump(dump, board);

        // find moves
        TMoveContainer moves;
        GenerateMoves(moves, board, EPieceColor::White);
        EXPECT_EQ(moves.MovesCount, 32);
    }
}

TEST(Dragon, MovesPosition) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 16 * 16) {
        auto board = TBoard{/* columns = */ 16, /* rows = */ 16}
            .SetBoardPiece({.Column = 8, .Row = 7}, WhiteDragon)

            .SetBoardPiece({.Column = 10, .Row = 8}, WhiteDummy)
            .SetBoardPiece({.Column = 9, .Row = 9}, WhiteDummy)
            .SetBoardPiece({.Column = 7, .Row = 9}, WhiteDummy)
            .SetBoardPiece({.Column = 6, .Row = 8}, WhiteDummy)
            .SetBoardPiece({.Column = 7, .Row = 5}, WhiteDummy)
            .SetBoardPiece({.Column = 6, .Row = 6}, WhiteDummy)
            .SetBoardPiece({.Column = 9, .Row = 5}, WhiteDummy)
            .SetBoardPiece({.Column = 10, .Row = 6}, WhiteDummy)

            .SetBoardPiece({.Column = 12, .Row = 7}, WhiteDummy)
            .SetBoardPiece({.Column = 8, .Row = 11}, WhiteDummy)
            .SetBoardPiece({.Column = 4, .Row = 7}, WhiteDummy)
            .SetBoardPiece({.Column = 8, .Row = 3}, WhiteDummy)
            .SetBoardPiece({.Column = 11, .Row = 10}, WhiteDummy)
            .SetBoardPiece({.Column = 11, .Row = 4}, WhiteDummy)
            .SetBoardPiece({.Column = 5, .Row = 10}, WhiteDummy)
            .SetBoardPiece({.Column = 5, .Row = 4}, WhiteDummy)

            .SetBoardPiece({.Column = 3, .Row = 5}, WhiteDummy)
            .SetBoardPiece({.Column = 3, .Row = 9}, WhiteDummy)
            .SetBoardPiece({.Column = 6, .Row = 2}, WhiteDummy)
            .SetBoardPiece({.Column = 6, .Row = 12}, WhiteDummy)
            .SetBoardPiece({.Column = 10, .Row = 2}, WhiteDummy)
            .SetBoardPiece({.Column = 10, .Row = 12}, WhiteDummy)
            .SetBoardPiece({.Column = 13, .Row = 5}, WhiteDummy)
            .SetBoardPiece({.Column = 13, .Row = 9}, WhiteDummy)

            .SetBoardPiece({.Column = 2, .Row = 7}, WhiteDummy)
            .SetBoardPiece({.Column = 14, .Row = 7}, WhiteDummy)
            .SetBoardPiece({.Column = 8, .Row = 13}, WhiteDummy)
            .SetBoardPiece({.Column = 8, .Row = 1}, WhiteDummy)
            .SetBoardPiece({.Column = 12, .Row = 11}, WhiteDummy)
            .SetBoardPiece({.Column = 12, .Row = 3}, WhiteDummy)
            .SetBoardPiece({.Column = 4, .Row = 11}, WhiteDummy)
            .SetBoardPiece({.Column = 4, .Row = 3}, WhiteDummy);

        // check initial position
        std::string_view dump =
            "╔════════════════╗"
            "║                ║"
            "║                ║"
            "║        ○       ║"
            "║      ○   ○     ║"
            "║    ○   ○   ○   ║"
            "║     ○     ○    ║"
            "║   ○   ○ ○   ○  ║"
            "║      ○   ○     ║"
            "║  ○ ○   D   ○ ○ ║"
            "║      ○   ○     ║"
            "║   ○   ○ ○   ○  ║"
            "║     ○     ○    ║"
            "║    ○   ○   ○   ║"
            "║      ○   ○     ║"
            "║        ○       ║"
            "║                ║"
            "╚════════════════╝";
        CheckDump(dump, board);

        // find moves
        TMoveContainer moves;
        GenerateMoves(moves, board, EPieceColor::White);
        EXPECT_EQ(moves.MovesCount, 0);
    }
}
