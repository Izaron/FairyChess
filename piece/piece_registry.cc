#include "piece_registry.h"

namespace NFairyChess {

namespace {

constinit TPieceRegistry PieceRegistry;

} // namespace

TPieceRegistry& TPieceRegistry::Get() {
    return PieceRegistry;
}

void TPieceRegistry::AddPieceInfo(std::size_t cost) {
}

} // namespace NFairyChess
