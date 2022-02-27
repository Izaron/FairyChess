#include "graphics.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

const std::string ImageFilesFolder = "images/";

constexpr unsigned int SquarePixelSize = 60;

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

void CreateRenderWindow(sf::RenderWindow& renderWindow, const TBoard& board) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::VideoMode videoMode{/* modeWidth = */ board.GetColumns() * SquarePixelSize,
                            /* modeHeight = */ board.GetRows() * SquarePixelSize};
    renderWindow.create(videoMode, "Fairy chess",
                        sf::Style::Titlebar | sf::Style::Close, settings);
    renderWindow.setVerticalSyncEnabled(true);
}

} // namespace

const TBoard& TGraphics::GetCurrentBoard() const {
    return *CurrentBoard_;
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

void TGraphics::RenderCurrentBoard(sf::RenderTarget& renderTarget) {
    // draw board squares
    for (int col = 0; col < CurrentBoard_->GetColumns(); ++col) {
        for (int row = 0; row < CurrentBoard_->GetRows(); ++row) {
            sf::RectangleShape rect{sf::Vector2f{SquarePixelSize, SquarePixelSize}};
            rect.setPosition(SquarePixelSize * col,
                             SquarePixelSize * (CurrentBoard_->GetRows() - 1 - row));

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

            renderTarget.draw(rect);
        }
    }

    // draw every piece
    for (TBoard::TBoardPieceWithPosition iter : *CurrentBoard_) {
        TBoardPosition pos = iter.Position;
        TBoardPiece boardPiece = iter.BoardPiece;

        sf::Sprite sprite;
        auto& textures = (boardPiece.GetColor() == EPieceColor::White ? WhiteTextures_ : BlackTextures_);
        sprite.setTexture(textures.at(boardPiece.GetPieceId()));
        const float scaleFactor = static_cast<float>(SquarePixelSize)
            / static_cast<float>(sprite.getTexture()->getSize().x);
        sprite.setScale(scaleFactor, scaleFactor);

        sprite.setPosition(pos.Column * SquarePixelSize,
                           (CurrentBoard_->GetRows() - 1 - pos.Row) * SquarePixelSize);

        renderTarget.draw(sprite);
    }
}

void TGraphics::UpdateCurrentBoard(const TBoard& board) {
    if (CurrentBoard_) {
        std::set<std::pair<int, int>> newChangedSquares;
        for (int col = 0; col < board.GetColumns(); ++col) {
            for (int row = 0; row < board.GetRows(); ++row) {
                TBoardPiece prevBoardPiece = CurrentBoard_->GetBoardPiece({.Column = col, .Row = row});
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
            CurrentBoard_ = board;
        }
    } else {
        CurrentBoard_ = board;
    }
}

TGraphicsWindowRender::TGraphicsWindowRender(const TBoard& initialBoard) {
    if (!LoadTextures()) {
        throw std::runtime_error("Can't load textures");
    }
    UpdateCurrentBoard(initialBoard);
    CreateRenderWindow(Window_, GetCurrentBoard());

    const auto renderingThreadFunc = [this] {
        while (Window_.isOpen()) {
            sf::Event event;
            while (Window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    Window_.close();
                }
            }

            Window_.clear();
            {
                std::lock_guard<std::mutex> guard(BoardMutex_);
                RenderCurrentBoard(Window_);
            }
            Window_.display();
        }
    };

    RenderingThread_ = std::thread{renderingThreadFunc};
}

TGraphicsWindowRender::~TGraphicsWindowRender() {
    RenderingThread_.join();
}

void TGraphicsWindowRender::OnNewBoard(const TBoard& board) {
    {
        std::lock_guard<std::mutex> guard(BoardMutex_);
        UpdateCurrentBoard(board);
    }
}

TGraphicsFileRender::TGraphicsFileRender(const TBoard& initialBoard) {
    if (!LoadTextures()) {
        throw std::runtime_error("Can't load textures");
    }
    UpdateCurrentBoard(initialBoard);
    OnNewBoard(initialBoard); // save the initial board image
}

void TGraphicsFileRender::OnNewBoard(const TBoard& board) {
    UpdateCurrentBoard(board);

    sf::RenderTexture renderTexture;
    renderTexture.create(/* modeWidth = */ board.GetColumns() * SquarePixelSize,
                         /* modeHeight = */ board.GetRows() * SquarePixelSize);
    RenderCurrentBoard(renderTexture);

    std::string imageFilename = GetNewImageFilename();
    sf::Image image = renderTexture.getTexture().copyToImage();
    image.flipVertically();
    image.saveToFile(imageFilename);
}

std::string TGraphicsFileRender::GetNewImageFilename() {
    char numStr[5];
    sprintf(numStr, "%04d", FilesCount_);
    std::string filename = "gameplay_images/board" + std::string{numStr} + ".png";
    ++FilesCount_;
    return filename;
}

} // namespace NFairyChess
