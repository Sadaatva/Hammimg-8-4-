#ifndef ENCODE_H
#define ENCODE_H

#include <bitset>

bool ans(bool n1, bool n2, bool n3, bool n4);

std::bitset<8> encodeHam(std::bitset<4> data);
std::bitset<16> encode(int c);

#endif 

