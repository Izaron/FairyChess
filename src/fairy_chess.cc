#include <SFML/Graphics.hpp>
#include "boards_assembler.h"
#include "evaluator.h"
#include "graphics.h"
#include "minimax.h"
#include "pretty_printer.h"

#include <thread>
#include <iostream>

using namespace NFairyChess;

namespace {

std::mutex BoardMutex;

void RenderingThread(sf::RenderWindow& window, TGraphics& graphics, TBoard& board) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        TBoard boardCopy;
        {
            std::lock_guard<std::mutex> guard(BoardMutex);
            boardCopy = board;
        }

        window.clear();
        graphics.DrawBoard(boardCopy);
        window.display();
    }
}

} // namespace

int main() {
    // create board
    //TBoard board = TBoardAssembler::AssembleVanillaBoard();
    //TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();
    //TBoard board = TBoardAssembler::AssembleHordeBoard();
    //TBoard board = TBoardAssembler::AssemblePeasantsRevoltBoard();
    TBoard board = TBoardAssembler::AssembleWeakBoard();

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

    std::thread renderingThread{RenderingThread, std::ref(window), std::ref(graphics),
                                std::ref(board)};

    std::cout << "Current board:" << std::endl;
    DumpBoard(board, std::cout, /* useNewline = */ true);

    EPieceColor currentColor = EPieceColor::White;

    {
        TMinimax minimax{4};
        int analyzedBoards = minimax.GetAnalyzedBoards();
        for (int i = 0; i < 300; ++i) {
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
                break;
            }
            TMove move = std::get<TMove>(moveOrGameEnd);

            int newAnalyzedBoard = minimax.GetAnalyzedBoards();

            std::cerr << "\nFound a new move " << i << ", analyzed boards: "
                << newAnalyzedBoard << ", time taken: " << secs << "s"
                << ", average speed " << (newAnalyzedBoard - analyzedBoards) / secs
                << " boards/s" << std::endl;

            {
                std::lock_guard<std::mutex> guard(BoardMutex);
                board = ApplyMove(board, move);
            }

            TEvaluationResult eval = Evaluate(board);
            std::cerr << "Current white score: " << eval.WhiteCost + 10 * eval.WhiteAvailableMoves
                << ", black score: " << eval.BlackCost + 10 * eval.BlackAvailableMoves << std::endl;

            std::cout << "Current board after move:" << std::endl;
            DumpBoard(board, std::cout, /* useNewline = */ true);
            currentColor = InvertPieceColor(currentColor);

            analyzedBoards = newAnalyzedBoard;
        }
    }

    renderingThread.join();
}
