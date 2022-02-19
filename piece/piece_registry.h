#pragma once

#include <unordered_set>

#include "piece.h"

namespace NFairyChess {

struct TPieceInfo {
    std::size_t Cost;
};

class TPieceRegistry {
public:
    static void AddPieceInfo(std::size_t pieceId, TPieceInfo pieceInfo);
    static const TPieceInfo* GetPieceInfo(std::size_t pieceId);
};

template<TPieceType Type>
struct TPieceRegistrator {
    TPieceRegistrator() {
        TPieceInfo pieceInfo{.Cost = Type::Cost};
        TPieceRegistry::AddPieceInfo(Type::PieceId, std::move(pieceInfo));
    }
};

} // namespace NFairyChess

#define MACRO_CONCAT( x, y ) x##y

#define REGISTER_FIGURE(Type) \
static ::NFairyChess::TPieceRegistrator<Type> \
MACRO_CONCAT(ScenarioRegistrator, __COUNTER__);
