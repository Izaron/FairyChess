#include <gtest/gtest.h>
#include "boards_assembler.h"
#include "pretty_printer.h"

using namespace NFairyChess;

TEST(BoardsAssemplerTest, VanillaBoard) {
    TBoard board = TBoardAssembler::AssembleVanillaBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, ChargeOfTheLightBrigadeBoard) {
    TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();

    std::string_view dump =
        "╔════════╗"
        "║♞♞♞♞♚♞♞♞║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║ ♕ ♕♔ ♕ ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, HordeBoard) {
    TBoard board = TBoardAssembler::AssembleHordeBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║ ♙♙  ♙♙ ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, PeasantsRevoltBoard) {
    TBoard board = TBoardAssembler::AssemblePeasantsRevoltBoard();

    std::string_view dump =
        "╔════════╗"
        "║ ♞♞ ♚♞♞ ║"
        "║    ♟︎   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║    ♔   ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, WeakBoard) {
    TBoard board = TBoardAssembler::AssembleWeakBoard();

    std::string_view dump =
        "╔════════╗"
        "║♞♞♞♞♚♞♞♞║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║  ♟︎  ♟︎  ║"
        "║ ♟︎♟︎♟︎♟︎♟︎♟︎ ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, BerolinaBoard) {
    TBoard board = TBoardAssembler::AssembleBerolinaBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}