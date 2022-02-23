#include "zobrist_hashing.h"

#include <unordered_map>

namespace NFairyChess {

namespace {

constexpr std::size_t BoardMaxSize = std::tuple_size<TBoard::TBoardPiecesContainer>::value;

static std::unordered_map<TStorageType, uint32_t> RandomNumbers[BoardMaxSize];
static std::unordered_map<int, uint32_t> DepthRandomNumbers;
constexpr uint32_t BlackColorXor = 0xCAFEF00D;

// use inhouse fast pseudorandom number generator
uint32_t seed = 0xDEC0DE;
uint32_t XorShift32() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
    return seed;
}

template<typename T>
uint32_t GetOrCreateRandomNumber(std::unordered_map<T, uint32_t>& map, T key) {
    if (const auto iter = map.find(key); iter != map.end()) {
        // random number for this key found
        return iter->second;
    } else {
        // random number not found, create it
        const uint32_t number = XorShift32();
        map[key] = number;
        return number;
    }
}

} // namespace

uint32_t TZobristHashing::CalculateHash(const TBoard& board, EPieceColor playerColor, int minimaxDepth) {
    uint32_t hash = GetOrCreateRandomNumber(DepthRandomNumbers, minimaxDepth);
    if (playerColor == EPieceColor::Black) {
        hash ^= BlackColorXor;
    }
    for (TBoard::TBoardPieceWithPosition iter : board) {
        const int col = iter.Position.Column;
        const int row = iter.Position.Row;
        const TStorageType boardPieceEncoded = iter.BoardPiece.GetView().GetValue();

        auto& randomNumbers = RandomNumbers[col * board.GetRows() + row];
        hash ^= GetOrCreateRandomNumber(randomNumbers, boardPieceEncoded);
    }
    return hash;
}

uint32_t TZobristHashing::CalculateSimpleHash(const TBoard& board) {
    return CalculateHash(board, /* color = */ EPieceColor::White, /* depth = */ 0);
}

} // namespace NFairyChess
