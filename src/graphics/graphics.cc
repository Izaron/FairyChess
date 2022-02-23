#include "graphics.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

const std::string ImageFilesFolder = "images/";

const sf::Color WhiteSquareColor = sf::Color{239, 217, 182};
const sf::Color BlackSquareColor = sf::Color{180, 136, 100};

const sf::Color ChangedWhiteSquareColor = sf::Color{204, 210, 117};
const sf::Color ChangedBlackSquareColor = sf::Color{169, 162, 69};

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
    if (PrevBoard_) {
        std::set<std::pair<int, int>> newChangedSquares;
        for (int col = 0; col < board.GetColumns(); ++col) {
            for (int row = 0; row < board.GetRows(); ++row) {
                TBoardPiece prevBoardPiece = PrevBoard_->GetBoardPiece({.Column = col, .Row = row});
                TBoardPiece nextBoardPiece = board.GetBoardPiece({.Column = col, .Row = row});

                if (prevBoardPiece.IsEmpty() && nextBoardPiece.IsEmpty()) {
                    continue;
                }

                bool isDifferent = false;
                if (prevBoardPiece.IsEmpty() != nextBoardPiece.IsEmpty()) {
                    isDifferent = true;
                } else if (prevBoardPiece.GetColor() != nextBoardPiece.GetColor()) {
                    isDifferent = true;
                } else if (prevBoardPiece.GetPieceId() != nextBoardPiece.GetPieceId()) {
                    isDifferent = true;
                }

                if (isDifferent) {
                    newChangedSquares.insert({col, row});
                }
            }
        }
        if (newChangedSquares != ChangedSquares_ && !newChangedSquares.empty()) {
            ChangedSquares_ = newChangedSquares;
            PrevBoard_ = board;
        }
    } else {
        PrevBoard_ = board;
    }

    // draw board squares
    for (int col = 0; col < board.GetColumns(); ++col) {
        for (int row = 0; row < board.GetRows(); ++row) {
            sf::RectangleShape rect{sf::Vector2f{TGraphics::SquarePixelSize, TGraphics::SquarePixelSize}};
            rect.setPosition(TGraphics::SquarePixelSize * col,
                             TGraphics::SquarePixelSize * (board.GetRows() - 1 - row));

            const bool isWhiteSquare = (col + row) % 2 == 0;
            const bool isChangedSquare = ChangedSquares_.contains({col, row});
            if (isWhiteSquare) {
                if (isChangedSquare) {
                    rect.setFillColor(ChangedWhiteSquareColor);
                } else {
                    rect.setFillColor(WhiteSquareColor);
                }
            } else {
                if (isChangedSquare) {
                    rect.setFillColor(ChangedBlackSquareColor);
                } else {
                    rect.setFillColor(BlackSquareColor);
                }
            }

            Window_.draw(rect);
        }
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
