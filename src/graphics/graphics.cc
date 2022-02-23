#include "graphics.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

const std::string ImageFilesFolder = "images/";
const sf::Color WhiteSquareColor = sf::Color{254, 206, 159};
const sf::Color BlackSquareColor = sf::Color{208, 139, 72};

bool LoadTexture(sf::Texture& texture, std::string_view imageFile) {
    if (!texture.loadFromFile(ImageFilesFolder + std::string{imageFile})) {
        return false;
    }
    texture.setSmooth(true);
    return true;
}

} // namespace

TGraphics::TGraphics(sf::RenderWindow& window, int cols, int rows)
    : Window_{window}
{
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            sf::RectangleShape rect{sf::Vector2f{TGraphics::SquarePixelSize, TGraphics::SquarePixelSize}};
            rect.setPosition(TGraphics::SquarePixelSize * col, TGraphics::SquarePixelSize * row);
            if ((col + row) % 2 == 0) {
                rect.setFillColor(WhiteSquareColor);
            } else {
                rect.setFillColor(BlackSquareColor);
            }
            BoardSquaresShapes_.push_back(std::move(rect));
        }
    }
}

bool TGraphics::LoadTextures() {
    for (auto [pieceId, pieceInfo] : TPieceRegistry::GetAllPieceInfos()) {
        if (!LoadTexture(WhiteTextures_[pieceId], pieceInfo->WhiteImageFile) ||
            !LoadTexture(BlackTextures_[pieceId], pieceInfo->BlackImageFile))
        {
            return false;
        }
    }
    return true;
}

void TGraphics::DrawBoard(const TBoard& board) {
    // draw board squares
    for (const auto& shape : BoardSquaresShapes_) {
        Window_.draw(shape);
    }

    // draw every piece
    for (TBoard::TBoardPieceWithPosition iter : board) {
        TBoardPosition pos = iter.Position;
        TBoardPiece boardPiece = iter.BoardPiece;

        sf::Sprite sprite;
        auto& textures = (boardPiece.GetColor() == EPieceColor::White ? WhiteTextures_ : BlackTextures_);
        sprite.setTexture(textures.at(boardPiece.GetPieceId()));
        const float scaleFactor = static_cast<float>(SquarePixelSize)
            / static_cast<float>(sprite.getTexture()->getSize().x);
        sprite.setScale(scaleFactor, scaleFactor);

        sprite.setPosition(pos.Column * SquarePixelSize,
                           (board.GetRows() - 1 - pos.Row) * SquarePixelSize);

        Window_.draw(sprite);
    }
}

} // namespace NFairyChess
