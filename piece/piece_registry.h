#pragma once

#include <functional>
#include <unordered_set>

#include "piece.h"
#include "board_piece.h"
#include "move_generator.h"

namespace NFairyChess {

struct TPieceInfo {
    std::size_t Cost;
    char DumpSymbol;
    std::function<void(TBoardPiece, TMoveContext)> FillMovesFn;
};

namespace NImpl {

inline std::array<bool, 1024> HavePieceInfo;
inline std::array<TPieceInfo, 1024> PieceInfo;

} // namespace NImpl


class TPieceRegistry {
public:
    static void AddPieceInfo(std::size_t pieceId, TPieceInfo pieceInfo);
    static const TPieceInfo* GetPieceInfo(std::size_t pieceId);
};

template<TPieceType Type>
struct TPieceRegistrator {
    TPieceRegistrator() {
        constexpr auto fillMovesFn = [](TBoardPiece boardPiece, TMoveContext moveContext) {
            Type piece = boardPiece.GetPieceOrEmpty<Type>().GetPiece();
            piece.FillMoves(std::move(moveContext));
        };
        // Dump symbol is optional. If there is no dump symbol, use '?'
        char dumpSymbol = '?';
        if constexpr (requires { Type::DumpSymbol; }) {
            dumpSymbol = Type::DumpSymbol;
        }
        TPieceInfo pieceInfo{.Cost = Type::Cost,
                             .DumpSymbol = dumpSymbol,
                             .FillMovesFn = fillMovesFn};
        TPieceRegistry::AddPieceInfo(Type::PieceId, pieceInfo);
    }
};

} // namespace NFairyChess

#define MACRO_CONCAT( x, y ) x##y

#define REGISTER_FIGURE(Type) \
static ::NFairyChess::TPieceRegistrator<Type> \
MACRO_CONCAT(ScenarioRegistrator, __COUNTER__);
