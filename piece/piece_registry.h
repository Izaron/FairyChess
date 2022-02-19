#pragma once

#include <functional>
#include <unordered_set>

#include "piece.h"
#include "board_piece.h"
#include "move_generator.h"

namespace NFairyChess {

struct TPieceInfo {
    std::size_t Cost;
    std::function<void(TBoardPiece, TMoveContext)> FillMovesFn;
};

class TPieceRegistry {
public:
    static void AddPieceInfo(std::size_t pieceId, TPieceInfo pieceInfo);
    static const TPieceInfo* GetPieceInfo(std::size_t pieceId);
};

template<TPieceType Type>
struct TPieceRegistrator {
    TPieceRegistrator() {
        auto fillMovesFn = [](TBoardPiece boardPiece, TMoveContext moveContext) {
            Type piece = boardPiece.GetPieceOrEmpty<Type>().GetPiece();
            piece.FillMoves(std::move(moveContext));
        };
        TPieceInfo pieceInfo{.Cost = Type::Cost};
        TPieceRegistry::AddPieceInfo(Type::PieceId, std::move(pieceInfo));
    }
};

} // namespace NFairyChess

#define MACRO_CONCAT( x, y ) x##y

#define REGISTER_FIGURE(Type) \
static ::NFairyChess::TPieceRegistrator<Type> \
MACRO_CONCAT(ScenarioRegistrator, __COUNTER__);
