#include <gtest/gtest.h>
#include "encode.cpp"
#include "decode.cpp"

TEST(EncodeTest, EncodeMaxValue) {
    std::bitset<16> encoded = encode(255);
    EXPECT_EQ(encoded.to_string(), "1110101011101010");
}

TEST(EncodeTest, EncodeRandomValue) {
    std::bitset<16> encoded = encode(85);
    EXPECT_EQ(encoded.to_string(), "0111001101110011");
}

TEST(DecodeTest, BasicDecode) {
    short s1 = 0b1101011011101101;
    int a1 = -1;
    EXPECT_EQ(decode(s1), a1);

    short s2 = 0b1100011011101101;
    int a2 = 158;
    EXPECT_EQ(decode(s2), a2);

    short s3 = 0b001010111110110;
    int a3 = 13; // error in p4
    EXPECT_EQ(decode(s3), a3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


