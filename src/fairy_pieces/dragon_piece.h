#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TDragonPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 27;
    static constexpr std::size_t Cost = 500;
    static constexpr std::string_view WhiteDumpStr = "D";
    static constexpr std::string_view BlackDumpStr = "d";
    static constexpr std::string_view WhiteImageFile = "dragon_white.png";
    static constexpr std::string_view BlackImageFile = "dragon_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TDragonPiece);

} // namespace NFairyChess::NFairyPieces
