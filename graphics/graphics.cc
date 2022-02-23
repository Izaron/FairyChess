#include "graphics.h"
#include "piece_registry.h"

namespace NFairyChess {

namespace {

const std::string ImageFilesFolder = "images/";

bool LoadTexture(sf::Texture& texture, std::string_view imageFile) {
    return texture.loadFromFile(ImageFilesFolder + std::string{imageFile});
}

} // namespace

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

} // namespace NFairyChess
