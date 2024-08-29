#include <libcrc/crc.hpp>

#include <gtest/gtest.h>

TEST(Crc8Suite, ZeroLengthInputReturnsInitialValue) {
    crc::Crc8 crc_a{0x07};
    crc::Crc8 crc_b{0x2F, 0xFF};
    std::array<uint8_t, 0> input{};

    EXPECT_EQ(crc_a.crc(&input[0], &input[0]), 0);
    EXPECT_EQ(crc_b.crc(&input[0], &input[0]), 0xFF);
}

TEST(Crc8Suite, NonZeroLengthInputReturnsExpectedValue) {
    crc::Crc8 crc_a{0x07};
    crc::Crc8 crc_b{0x2F, 0xFF};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[1]), 0x97);
    EXPECT_EQ(crc_b.crc(&input[0], &input[1]), 0xB0);
    EXPECT_EQ(crc_a.crc(&input[0], &input[2]), 0x72);
    EXPECT_EQ(crc_b.crc(&input[0], &input[2]), 0xBD);
    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0xC0);
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0x56);
}

TEST(Crc8Suite, ArbitraryLengthInputReturnExpectedXoredValue) {
    crc::Crc8 crc_a{0x2F, 0xFF, 0xFF};
    crc::Crc8 crc_b{0x2F, 0xFF, 0x9F};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[0]), 0xFF ^ 0xFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[0]), 0xFF ^ 0x9F);
    EXPECT_EQ(crc_a.crc(&input[0], &input[1]), 0xB0 ^ 0xFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[1]), 0xB0 ^ 0x9F);
    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0x56 ^ 0xFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0x56 ^ 0x9F);
}
