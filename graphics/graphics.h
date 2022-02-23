#pragma once

#include <SFML/Graphics.hpp>
#include "board.h"

namespace NFairyChess {

class TGraphics {
public:
    bool LoadTextures();
    void DrawBoard(const TBoard& board);

private:
    // maps PieceId to texture
    std::unordered_map<std::size_t, sf::Texture> WhiteTextures_;
    std::unordered_map<std::size_t, sf::Texture> BlackTextures_;
};

} // namespace NFairyChess
