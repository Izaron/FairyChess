#pragma once

#include "board.h"

namespace NFairyChess {

struct TBoardAssembler {
    // vanilla board
    static TBoard AssembleVanillaBoard();

    // standard board but different number of pieces
    static TBoard AssembleChargeOfTheLightBrigadeBoard();
    static TBoard AssembleHordeBoard();
    static TBoard AssemblePeasantsRevoltBoard();
    static TBoard AssembleWeakBoard();
    
    // standard board with fairy pieces
    static TBoard AssembleBerolinaBoard();
    static TBoard AssembleMadKingBoard();
};

} // namespace NFairyChess
