#pragma once

#include "piece.h"

namespace NFairyChess {

class TPieceRegistry {
public:
    static TPieceRegistry& Get();

public:
    void AddPieceInfo(std::size_t cost);
};

template<TPieceType Type>
struct TPieceRegistrator {
    TPieceRegistrator() {
        TPieceRegistry::Get().AddPieceInfo(Type::Cost);
    }
};

} // namespace NFairyChess

#define MACRO_CONCAT( x, y ) x##y

#define REGISTER_FIGURE(Type) \
static ::NFairyChess::TPieceRegistrator<Type> \
MACRO_CONCAT(ScenarioRegistrator, __COUNTER__);
