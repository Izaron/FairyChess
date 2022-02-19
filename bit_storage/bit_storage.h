#pragma once

#include <type_traits>

namespace NFairyChess {

// A type for bit storage should be integral
template<class T>
concept TPossibleStorageType = std::is_integral<T>::value;

template<TPossibleStorageType TType, std::size_t Begin, std::size_t End>
class TBitView {
public:
    explicit TBitView(TType& storage)
        : Storage_{storage}
    {}

    TBitView(const TBitView&) = delete;
    TBitView(TBitView&&) = delete;

    template<typename T = TType>
    T GetValue() const {
        // returns the value of the view
        constexpr TType croppingMask = (1LL << End) - 1;
        return static_cast<T>((Storage_ & croppingMask) >> Begin);
    }

    template<typename T = TType>
    void SetValue(T value) {
        // cast value of other type to the right type
        TType typedValue = static_cast<TType>(value);

        // clear the previous value of the view
        constexpr TType upperMask = (1LL << End) - 1;     // 111111111000
        constexpr TType lowerMask = (1LL << Begin) - 1;   // 111000000000
        constexpr TType viewMask = upperMask ^ lowerMask; // 000111111000
        constexpr TType invertedViewMask = ~viewMask;     // 111000000111
        Storage_ &= invertedViewMask;

        // shift value to the view's begin bit
        typedValue <<= Begin;

        // place value to the view
        Storage_ |= typedValue;
    }

private:
    TType& Storage_;
};

template<TPossibleStorageType TType>
class TBitStorage {
public:
    explicit TBitStorage(TType value = 0)
        : Storage_{value}
    {}

    //TBitStorage(const TBitStorage&) = delete;
    //TBitStorage(TBitStorage&&) = delete;

    template<std::size_t Begin = 0, std::size_t End = sizeof(TType) * 8>
    auto GetView() {
        static_assert((Begin < End) && (End <= sizeof(TType) * 8));
        return TBitView<TType, Begin, End>(Storage_);
    }

private:
    TType Storage_;
};

} // namespace NFairyChess
