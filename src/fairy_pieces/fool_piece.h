#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TFoolPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 26;
    static constexpr std::size_t Cost = 500;
    static constexpr std::string_view WhiteDumpStr = "F";
    static constexpr std::string_view BlackDumpStr = "f";
    static constexpr std::string_view WhiteImageFile = "fool_white.png";
    static constexpr std::string_view BlackImageFile = "fool_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TFoolPiece);

} // namespace NFairyChess::NFairyPieces
