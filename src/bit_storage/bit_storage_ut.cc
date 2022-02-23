#include <gtest/gtest.h>
#include "bit_storage.h"

using namespace NFairyChess;

TEST(BitStorageTest, EmptyIsZero) {
    TBitStorage<char8_t> storage;
    auto value = storage.GetView().GetValue();

    // the returned value is same as template
    static_assert(std::is_same_v<decltype(value), char8_t>);

    // the returned value is zero
    EXPECT_EQ(value, 0);
}

TEST(BitStorageTest, SetWholeValue) {
    TBitStorage<char8_t> storage;
    storage.GetView().SetValue(128);
    EXPECT_EQ(storage.GetView().GetValue(), 128);
}

TEST(BitStorageTest, SetLowerBit) {
    TBitStorage<char8_t> storage;
    auto view = storage.GetView<0, 1>();
    view.SetValue(1);
    // the view's value is 1, the overall value is 1
    EXPECT_EQ(view.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 1);
}

TEST(BitStorageTest, SetUpperBit) {
    TBitStorage<char8_t> storage;
    auto view = storage.GetView<7, 8>();
    view.SetValue(1);
    // the view's value is 1, the overall value is 1
    EXPECT_EQ(view.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 128);
}

TEST(BitStorageTest, SetLatticeBits) {
    // the initial value is 10101010 = 170
    TBitStorage<char8_t> storage{0b10101010};
    EXPECT_EQ(storage.GetView().GetValue(), 0b10101010);

    // set 1st zero
    auto v1 = storage.GetView<0, 1>();
    EXPECT_EQ(v1.GetValue(), 0);
    v1.SetValue(1);
    EXPECT_EQ(v1.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 0b10101011);

    // set 2nd zero
    auto v2 = storage.GetView<2, 3>();
    EXPECT_EQ(v2.GetValue(), 0);
    v2.SetValue(1);
    EXPECT_EQ(v2.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 0b10101111);

    // set 3rd zero
    auto v3 = storage.GetView<4, 5>();
    EXPECT_EQ(v3.GetValue(), 0);
    v3.SetValue(1);
    EXPECT_EQ(v3.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 0b10111111);

    // set 4th zero
    auto v4 = storage.GetView<6, 7>();
    EXPECT_EQ(v4.GetValue(), 0);
    v4.SetValue(1);
    EXPECT_EQ(v4.GetValue(), 1);
    EXPECT_EQ(storage.GetView().GetValue(), 0b11111111);
}

TEST(BitStorageTest, ConvertToEnum) {
    enum class SomeState {
        Zero, // 0
        One, // 1
        Two, // 2
    };

    TBitStorage<char8_t> storage;
    auto v1 = storage.GetView<0, 2>();
    EXPECT_EQ(v1.GetValue<SomeState>(), SomeState::Zero);

    v1.SetValue(SomeState::One);
    EXPECT_EQ(v1.GetValue<SomeState>(), SomeState::One);

    v1.SetValue(SomeState::Two);
    EXPECT_EQ(v1.GetValue<SomeState>(), SomeState::Two);
}
