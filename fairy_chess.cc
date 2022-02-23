#include "boards_assembler.h"
#include "minimax.h"
#include "pretty_printer.h"
#include "evaluator.h"

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
        int analyzedBoards = minimax.GetAnalyzedBoards();
        for (int i = 0; i < 20; ++i) {
            const clock_t begin_time = clock();
            TMove move = minimax.FindBestMove(board, currentColor);
            const double secs = double(clock () - begin_time) /  CLOCKS_PER_SEC;
            int newAnalyzedBoard = minimax.GetAnalyzedBoards();

            std::cerr << "\nFound a new move " << i << ", analyzed boards: "
                << newAnalyzedBoard << ", time taken: " << secs << "s"
                << ", average speed " << (newAnalyzedBoard - analyzedBoards) / secs
                << " boards/s" << std::endl;
            board = ApplyMove(board, move);
            TEvaluationResult eval = Evaluate(board);
            std::cerr << "Current white score: " << eval.WhiteCost + 10 * eval.WhiteAvailableMoves
                << ", black score: " << eval.BlackCost + 10 * eval.BlackAvailableMoves << std::endl;

            std::cout << "Current board after move:" << std::endl;
            DumpBoard(board, std::cout, /* useNewline = */ true);
            currentColor = InvertPieceColor(currentColor);

            analyzedBoards = newAnalyzedBoard;
        }
    }
}
