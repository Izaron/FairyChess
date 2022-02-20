#pragma once

#include "piece_registry.h"

namespace NFairyChess::NVanillaPieces {

class TRookPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 4;
    static constexpr std::size_t Cost = 500;
    static constexpr std::string_view WhiteDumpStr = "♖";
    static constexpr std::string_view BlackDumpStr = "♜";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TRookPiece);

} // namespace NFairyChess::NVanillaPieces
