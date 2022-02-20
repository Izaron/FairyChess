#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TKingPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 6;
    static constexpr std::size_t Cost = 20000;
    static constexpr std::string_view WhiteDumpStr = "♔";
    static constexpr std::string_view BlackDumpStr = "♚";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TKingPiece);

} // namespace NFairyChess::NVanillaPieces
