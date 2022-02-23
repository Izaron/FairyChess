#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TBishopPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 3;
    static constexpr std::size_t Cost = 300;
    static constexpr std::string_view WhiteDumpStr = "♗";
    static constexpr std::string_view BlackDumpStr = "♝";
    static constexpr std::string_view WhiteImageFile = "bishop_white.png";
    static constexpr std::string_view BlackImageFile = "bishop_black.png";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TBishopPiece);

} // namespace NFairyChess::NVanillaPieces
