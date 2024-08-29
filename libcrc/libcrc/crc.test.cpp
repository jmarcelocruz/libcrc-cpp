#include <libcrc/crc.hpp>

#include <gtest/gtest.h>

TEST(Crc8Suite, ZeroLengthInputReturnsZero) {
    crc::Crc8 crc{0x07};
    std::array<uint8_t,0> input{};

    EXPECT_EQ(crc.crc(&input[0], &input[0]), 0);
}

TEST(Crc8Suite, NonZeroLengthInputReturnsExpectedValue) {
    crc::Crc8 crc{0x07};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc.crc(&input[0], &input[1]), 0x97);
    EXPECT_EQ(crc.crc(&input[0], &input[2]), 0x72);
    EXPECT_EQ(crc.crc(&input[0], &input[3]), 0xC0);
}
