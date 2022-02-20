#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TQueenPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 5;
    static constexpr std::size_t Cost = 900;
    static constexpr std::string_view WhiteDumpStr = "♕";
    static constexpr std::string_view BlackDumpStr = "♛";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TQueenPiece);

} // namespace NFairyChess::NVanillaPieces
