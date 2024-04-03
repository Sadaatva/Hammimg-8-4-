#include <iostream>
#include <bitset>
#include "encode.h"

bool ans(bool n1, bool n2, bool n3, bool n4) {
    return (n1 + n2 + n3 + n4) % 2;
}

std::bitset<8> encodeHam(std::bitset<4> data) {
    bool d1 = data[0], d2 = data[1], d3 = data[2], d4 = data[3];
    bool p1, p2, p3, p4;

    p1 = ans(d1, d3, d4, 1);
    p2 = ans(d1, d2, d4, 1);
    p3 = ans(d1, d2, d3, 1);
    p4 = (1+p1+d1+p2+d2+p3+d3+d4)%2;

    std::bitset<8> encoded;
    encoded[0] = p1;
    encoded[1] = d1;
    encoded[2] = p2;
    encoded[3] = d2;
    encoded[4] = p3;
    encoded[5] = d3;
    encoded[6] = p4;
    encoded[7] = d4;

    return encoded;
}

std::bitset<16> encode(int c) {
    std::bitset<8> bits(c);

    std::bitset<4> firstPart(bits.to_string().substr(0, 4));
    std::bitset<4> secondPart(bits.to_string().substr(4, 4));

    std::bitset<8> encodedFirstPart = encodeHam(firstPart);
    std::bitset<8> encodedSecondPart = encodeHam(secondPart);

    std::bitset<16> encoded = (encodedFirstPart.to_ulong() << 8) | encodedSecondPart.to_ulong();

    return encoded;
}

