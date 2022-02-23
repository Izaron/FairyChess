#pragma once

#include "board.h"

namespace NFairyChess {

struct TBoardAssembler {
    static TBoard AssembleVanillaBoard();
    static TBoard AssembleChargeOfTheLightBrigadeBoard();
};

} // namespace NFairyChess
