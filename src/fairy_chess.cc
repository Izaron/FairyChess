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
    TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();

    // create render window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::VideoMode videoMode{/* modeWidth = */ board.GetColumns() * TGraphics::SquarePixelSize,
                            /* modeHeight = */ board.GetRows() * TGraphics::SquarePixelSize};
    sf::RenderWindow window(videoMode, "Fairy chess",
                            sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    // create graphics handler
    TGraphics graphics{window, board.GetColumns(), board.GetRows()};
    if (!graphics.LoadTextures()) {
        std::cerr << "Can't load textures!" << std::endl;
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        graphics.DrawBoard(board);
        window.display();
    }


    //TBoard board = TBoardAssembler::AssembleVanillaBoard();
    std::cout << "Current board:" << std::endl;
    DumpBoard(board, std::cout, /* useNewline = */ true);

    EPieceColor currentColor = EPieceColor::White;

    {
        TMinimax minimax{4};
        int analyzedBoards = minimax.GetAnalyzedBoards();
        for (int i = 0; i < 100; ++i) {
            const clock_t begin_time = clock();
            auto moveOrGameEnd = minimax.FindBestMoveOrGameEnd(board, currentColor);
            const double secs = double(clock () - begin_time) /  CLOCKS_PER_SEC;

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
            }
            TMove move = std::get<TMove>(moveOrGameEnd);

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