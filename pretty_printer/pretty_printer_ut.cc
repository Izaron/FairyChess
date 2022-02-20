#include <gtest/gtest.h>
#include "boards_assembler.h"
#include "pretty_printer.h"

using namespace NFairyChess;

TEST(PrettyPrinterTest, VanillaBoard) {
    TBoard board = TBoardAssembler::AssembleVanillaBoard();

    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║        ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}
