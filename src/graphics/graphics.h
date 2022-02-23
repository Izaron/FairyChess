#pragma once

#include <SFML/Graphics.hpp>
#include "board.h"

namespace NFairyChess {

class TGraphics {
public:
    TGraphics(sf::RenderWindow& window, int cols, int rows);

    bool LoadTextures();
    void DrawBoard(const TBoard& board);

public:
    static constexpr unsigned int SquarePixelSize = 80;

private:
    sf::RenderWindow& Window_;

    // maps PieceId to texture
    std::unordered_map<std::size_t, sf::Texture> WhiteTextures_;
    std::unordered_map<std::size_t, sf::Texture> BlackTextures_;

    std::vector<sf::RectangleShape> BoardSquaresShapes_;
};

} // namespace NFairyChess
