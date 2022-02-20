#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TKnightPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 2;
    static constexpr std::size_t Cost = 300;
    static constexpr std::string_view WhiteDumpStr = "♘";
    static constexpr std::string_view BlackDumpStr = "♞";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TKnightPiece);

} // namespace NFairyChess::NVanillaPieces
