#include "piece_registry.h"

namespace NFairyChess {

void TPieceRegistry::AddPieceInfo(std::size_t pieceId, TPieceInfo pieceInfo) {
    NImpl::HavePieceInfo[pieceId] = true;
    NImpl::PieceInfo[pieceId] = std::move(pieceInfo);
}

const TPieceInfo* TPieceRegistry::GetPieceInfo(std::size_t pieceId) {
    if (!NImpl::HavePieceInfo[pieceId]) {
        return nullptr;
    }
    return &NImpl::PieceInfo[pieceId];
}

} // namespace NFairyChess
