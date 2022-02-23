#include <SFML/Graphics.hpp>
#include "boards_assembler.h"
#include "evaluator.h"
#include "graphics.h"
#include "minimax.h"
#include "pretty_printer.h"

#include <iostream>

using namespace NFairyChess;

int main() {
    TGraphics graphics;
    if (!graphics.LoadTextures()) {
        std::cerr << "Can't load textures!" << std::endl;
        return 1;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("prikol.png")) {
        std::cerr << "NO U" << std::endl;
        return 0;
    }
    texture.setSmooth(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(480, 480), "Fairy chess",
                            sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.15f, 0.15f));
    //sprite.scale(sf::Vector2f(0.3f, 0.3f));
    //sprite.scale(sf::Vector2f(3.2f, 3.2f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(sprite);
        window.display();
    }


    TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();
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
