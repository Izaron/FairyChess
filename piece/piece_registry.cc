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

std::vector<std::pair<std::size_t, const TPieceInfo*>> TPieceRegistry::GetAllPieceInfos() {
    std::vector<std::pair<std::size_t, const TPieceInfo*>> pieceInfos;
    for (std::size_t i = 0; i < NImpl::HavePieceInfo.size(); ++i) {
        if (NImpl::HavePieceInfo[i]) {
            pieceInfos.emplace_back(i, &NImpl::PieceInfo[i]);
        }
    }
    return pieceInfos;
}

} // namespace NFairyChess
