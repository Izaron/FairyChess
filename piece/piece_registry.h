#pragma once

#include <functional>
#include <unordered_set>

#include "piece.h"
#include "board_piece.h"
#include "move_generator.h"

namespace NFairyChess {

struct TPieceInfo {
    std::size_t Cost;
    std::string_view WhiteDumpStr;
    std::string_view BlackDumpStr;
    std::function<void(TBoardPiece, TMoveContext)> FillMovesFn;
    std::function<bool(TBoardPiece&)> AfterMoveApplyFn;
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
        // Dump symbols are optional. If there is no dump symbols, use '?'
        std::string_view whiteDumpStr = "?";
        std::string_view blackDumpStr = "?";
        if constexpr (requires { Type::WhiteDumpStr; Type::BlackDumpStr; }) {
            whiteDumpStr = Type::WhiteDumpStr;
            blackDumpStr = Type::BlackDumpStr;
        }

        // FillMovesFn is mandatory
        constexpr auto fillMovesFn = [](TBoardPiece boardPiece, TMoveContext moveContext) {
            Type piece = boardPiece.GetPieceOrEmpty<Type>().GetPiece();
            piece.FillMoves(std::move(moveContext));
        };

        // AfterMoveApply is optional
        std::function<bool(TBoardPiece&)> afterMoveApplyFn;
        if constexpr (requires { &Type::AfterMoveApply; }) {
            afterMoveApplyFn = [](TBoardPiece& boardPiece) {
                Type piece = boardPiece.GetPieceOrEmpty<Type>().GetPiece();
                if (piece.AfterMoveApply()) {
                    boardPiece = TBoardPiece::CreateFromExisting<Type>(boardPiece.GetColor(), piece);
                    return true;
                }
                return false;
            };
        }

        TPieceInfo pieceInfo{.Cost = Type::Cost,
                             .WhiteDumpStr = whiteDumpStr,
                             .BlackDumpStr = blackDumpStr,
                             .FillMovesFn = fillMovesFn,
                             .AfterMoveApplyFn = std::move(afterMoveApplyFn)};
        TPieceRegistry::AddPieceInfo(Type::PieceId, pieceInfo);
    }
};

} // namespace NFairyChess

#define MACRO_CONCAT( x, y ) x##y

#define REGISTER_PIECE(Type) \
static ::NFairyChess::TPieceRegistrator<Type> \
MACRO_CONCAT(ScenarioRegistrator, __COUNTER__);
