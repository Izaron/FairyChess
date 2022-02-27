#pragma once

#include <SFML/Graphics.hpp>

#include "board.h"

#include <optional>
#include <set>
#include <thread>

namespace NFairyChess {

class TGraphics {
public:
    virtual ~TGraphics() = default;
    const TBoard& GetCurrentBoard() const;
    virtual void OnNewBoard(const TBoard& board) = 0;

protected:
    bool LoadTextures();
    void UpdateCurrentBoard(const TBoard& board);
    void RenderCurrentBoard(sf::RenderTarget& renderTarget);

private:
    // maps PieceId to texture
    std::unordered_map<std::size_t, sf::Texture> WhiteTextures_;
    std::unordered_map<std::size_t, sf::Texture> BlackTextures_;

    std::set<std::pair<int, int>> ChangedSquares_;
    std::optional<TBoard> CurrentBoard_;
};

class TGraphicsWindowRender : public TGraphics {
public:
    TGraphicsWindowRender(const TBoard& initialBoard);
    ~TGraphicsWindowRender();

    void OnNewBoard(const TBoard& board) override;

private:
    sf::RenderWindow Window_;
    std::mutex BoardMutex_;
    std::thread RenderingThread_;
};

class TGraphicsFileRender : public TGraphics {
public:
    TGraphicsFileRender(const TBoard& initialBoard);
    void OnNewBoard(const TBoard& board) override;

private:
    std::string GetNewImageFilename();

private:
    int FilesCount_ = 0;
};

} // namespace NFairyChess
