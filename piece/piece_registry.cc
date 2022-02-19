#include "piece_registry.h"

namespace NFairyChess {

namespace {

constinit std::array<bool, 1024> HavePieceInfo;
constinit std::array<TPieceInfo, 1024> PieceInfo;

} // namespace

void TPieceRegistry::AddPieceInfo(std::size_t pieceId, TPieceInfo pieceInfo) {
    HavePieceInfo[pieceId] = true;
    PieceInfo[pieceId] = std::move(pieceInfo);
}

const TPieceInfo* TPieceRegistry::GetPieceInfo(std::size_t pieceId) {
    if (!HavePieceInfo[pieceId]) {
        return nullptr;
    }
    return &PieceInfo[pieceId];
}

} // namespace NFairyChess
