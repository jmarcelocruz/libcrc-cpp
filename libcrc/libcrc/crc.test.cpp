#include <libcrc/crc.hpp>

#include <gtest/gtest.h>

TEST(Crc8Suite, ZeroLengthInputReturnsInitialValue) {
    crc::Crc8 crc_a{0x07};
    crc::Crc8 crc_b{0x2F, 0xFF};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

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

TEST(Crc8Suite, InputReflectionEnabledReturnsSameAsForReflectedInput) {
    crc::Crc8 crc_a{0x2F, 0xFF, 0x00, true};
    crc::Crc8 crc_b{0x2F, 0xFF, 0x00, false};
    std::array<uint8_t,3> input_a{0x31, 0x32, 0x33};
    std::array<uint8_t,3> input_b{0x8C, 0x4C, 0xCC};

    EXPECT_EQ(crc_a.crc(&input_a[0], &input_a[3]), crc_b.crc(&input_b[0], &input_b[3]));
}

TEST(Crc8Suite, OutputReflectionEnabledReturnsReflectedExpectedValue) {
    crc::Crc8 crc_a{0x2F, 0xFF, 0x00, false, true};
    crc::Crc8 crc_b{0x2F, 0xFF, 0x9F, false, true};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0x6A); /* reflected 0x56 */
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0xF5); /* reflected 0xC9 */
}

TEST(Crc32Suite, ZeroLengthInputReturnsInitialValue) {
    crc::Crc32 crc_a{0x4C11DB7};
    crc::Crc32 crc_b{0x4C11DB7, 0xFFFFFFFF};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[0]), 0);
    EXPECT_EQ(crc_b.crc(&input[0], &input[0]), 0xFFFFFFFF);
}

TEST(Crc32Suite, NonZeroLengthInputReturnsExpectedValue) {
    crc::Crc32 crc_a{0x4C11DB7};
    crc::Crc32 crc_b{0x4C11DB7, 0xFFFFFFFF};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[1]), 0xD0F37027);
    EXPECT_EQ(crc_b.crc(&input[0], &input[1]), 0x9EFBCF93);
    EXPECT_EQ(crc_a.crc(&input[0], &input[2]), 0x3F5B3A17);
    EXPECT_EQ(crc_b.crc(&input[0], &input[2]), 0x3FEC5E6A);
    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0x6E368C64);
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0xD952F164);
}

TEST(Crc32Suite, ArbitraryLengthInputReturnExpectedXoredValue) {
    crc::Crc32 crc_a{0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF};
    crc::Crc32 crc_b{0x4C11DB7, 0xFFFFFFFF, 0x9FFFFFFF};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[1]), 0x9EFBCF93 ^ 0xFFFFFFFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[1]), 0x9EFBCF93 ^ 0x9FFFFFFF);
    EXPECT_EQ(crc_a.crc(&input[0], &input[2]), 0x3FEC5E6A ^ 0xFFFFFFFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[2]), 0x3FEC5E6A ^ 0x9FFFFFFF);
    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0xD952F164 ^ 0xFFFFFFFF);
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0xD952F164 ^ 0x9FFFFFFF);
}

TEST(Crc32Suite, InputReflectionEnabledReturnsSameAsForReflectedInput) {
    crc::Crc32 crc_a{0x4C11DB7, 0xFFFFFFFF, 0, true};
    crc::Crc32 crc_b{0x4C11DB7, 0xFFFFFFFF, 0, false};
    std::array<uint8_t,3> input_a{0x31, 0x32, 0x33};
    std::array<uint8_t,3> input_b{0x8C, 0x4C, 0xCC};

    EXPECT_EQ(crc_a.crc(&input_a[0], &input_a[3]), crc_b.crc(&input_b[0], &input_b[3]));
}

TEST(Crc32Suite, OutputReflectionEnabledReturnsReflectedExpectedValue) {
    crc::Crc32 crc_a{0x4C11DB7, 0xFFFFFFFF, 0, false, true};
    crc::Crc32 crc_b{0x4C11DB7, 0xFFFFFFFF, 0x9FFFFFFF, false, true};
    std::array<uint8_t,3> input{0x31, 0x32, 0x33};

    EXPECT_EQ(crc_a.crc(&input[0], &input[3]), 0x268F4A9B); /* reflected 0xD952F164 */
    EXPECT_EQ(crc_b.crc(&input[0], &input[3]), 0xB970B564); /* reflected 0x46AD0E9B */
}
