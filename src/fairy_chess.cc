#include <SFML/Graphics.hpp>
#include "boards_assembler.h"
#include "evaluator.h"
#include "graphics.h"
#include "minimax.h"
#include "pretty_printer.h"

#include <iostream>

using namespace NFairyChess;

int main() {
    // create board
    TBoard board = TBoardAssembler::AssembleVanillaBoard();
    //TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();
    //TBoard board = TBoardAssembler::AssembleHordeBoard();
    //TBoard board = TBoardAssembler::AssemblePeasantsRevoltBoard();
    //TBoard board = TBoardAssembler::AssembleWeakBoard();
    //TBoard board = TBoardAssembler::AssembleBerolinaBoard();

    // create render window
    std::unique_ptr<TGraphics> graphics = std::make_unique<TGraphicsFileRender>(board);

    std::cout << "Current board:" << std::endl;
    DumpBoard(board, std::cout, /* useNewline = */ true);

    EPieceColor currentColor = EPieceColor::White;

    double totalSecondsElapsed = 0.0;
    {
        TMinimax minimax{4};
        int analyzedBoards = minimax.GetAnalyzedBoards();
        for (int i = 0; i < 1000; ++i) {
            const clock_t begin_time = clock();
            auto moveOrGameEnd = minimax.FindBestMoveOrGameEnd(board, currentColor);
            const double secondsElapsed = double(clock () - begin_time) /  CLOCKS_PER_SEC;

            if (const EGameEnd* gameEnd = std::get_if<EGameEnd>(&moveOrGameEnd)) {
                switch (*gameEnd) {
                    case EGameEnd::Checkmate: {
                        std::cerr << "Game ended, it's a checkmate!" << std::endl;
                        break;
                    }
                    case EGameEnd::Stalemate: {
                        std::cerr << "Game ended, it's a stalemate!" << std::endl;
                        break;
                    }
                }
                break;
            }
            TMove move = std::get<TMove>(moveOrGameEnd);

            int newAnalyzedBoard = minimax.GetAnalyzedBoards();

            totalSecondsElapsed += secondsElapsed;
            std::cerr << "\nFound a new move " << i << std::endl;
            std::cerr << "Analyzed boards: " << newAnalyzedBoard << std::endl;
            std::cerr << "Average speed for the move: " << (newAnalyzedBoard - analyzedBoards) / secondsElapsed
                << " boards/s" << std::endl;
            std::cerr << "Time taken for the move: " << secondsElapsed << "s" << std::endl;
            std::cerr << "Total time taken: " << totalSecondsElapsed << "s" << std::endl;

            board = ApplyMove(board, move);
            graphics->OnNewBoard(board);

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
