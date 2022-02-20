#include "boards_assembler.h"
#include "minimax.h"
#include "pretty_printer.h"

#include <iostream>

using namespace NFairyChess;

int main() {
    TBoard board = TBoardAssembler::AssembleVanillaBoard();
    std::cout << "Current board:" << std::endl;
    DumpBoard(board, std::cout, /* useNewline = */ true);

    EPieceColor currentColor = EPieceColor::White;

    for (int i = 0; i < 10; ++i) {
        TMinimax minimax{board, currentColor, 1};
        TMove move = minimax.FindBestMove();
        std::cerr << "\nFound a new move, analyzed boards: " << minimax.GetAnalyzedBoards() << std::endl;
        board = ApplyMove(board, move);

        std::cout << "Current board after move:" << std::endl;
        DumpBoard(board, std::cout, /* useNewline = */ true);
        currentColor = InvertPieceColor(currentColor);
    }
}
