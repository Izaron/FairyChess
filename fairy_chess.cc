#include "boards_assembler.h"
#include "minimax.h"
#include "pretty_printer.h"

#include <iostream>

using namespace NFairyChess;

int main() {
    //TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();
    TBoard board = TBoardAssembler::AssembleVanillaBoard();
    std::cout << "Current board:" << std::endl;
    DumpBoard(board, std::cout, /* useNewline = */ true);

    EPieceColor currentColor = EPieceColor::White;

    {
        TMinimax minimax{4};
        for (int i = 0; i < 200; ++i) {
            const clock_t begin_time = clock();
            TMove move = minimax.FindBestMove(board, currentColor);
            const double secs = double(clock () - begin_time) /  CLOCKS_PER_SEC;

            std::cerr << "\nFound a new move " << i << ", analyzed boards: "
                << minimax.GetAnalyzedBoards() << " time taken: " << secs << "s" << std::endl;
            board = ApplyMove(board, move);

            std::cout << "Current board after move:" << std::endl;
            DumpBoard(board, std::cout, /* useNewline = */ true);
            currentColor = InvertPieceColor(currentColor);
        }
    }
}
