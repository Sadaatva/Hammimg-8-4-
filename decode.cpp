#include <iostream>
#include <bitset>

int decodeHelper(int s) {
    std::bitset<8> bits(s);

    bool d1 = bits[0], d2 = bits[1], d3 = bits[2], d4 = bits[3];
    bool d5 = bits[4], d6 = bits[5], d7 = bits[6], d8 = bits[7];

    bool A = (d1 + d2 + d6 + d8) % 2 == 1;
    bool B = (d2 + d3 + d4 + d8) % 2 == 1;
    bool C = (d2 + d4 + d5 + d6) % 2 == 1;
    bool D = (d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8) % 2 == 1;
    
    if (A && B && C && D) {
        std::cout << "Packet accepted.\n";
    } else if (A && B && C && !D) {
        std::cout << "Error in p4, but packet accepted.\n";
        bits.flip(6);
    } else if ((!A || !B || !C) && !D) {
        std::cout << "Single error\n";
        if (!A && B && C) bits.flip(0);
        if (!A && !B && !C) bits.flip(1);
        if (A && !B && C) bits.flip(2);
        if (A && !B && !C) bits.flip(3);
        if (A && B && !C) bits.flip(4);
        if (!A && B && !C) bits.flip(5);
        if (!A && !B && C) bits.flip(7);
    } else if (!A && !B && !C && D) {
        std::cout << "Double error, rejecting packet.\n";
        return -1;
    } else {
        std::cout << "Unknown error condition.\n";
        return -1;
    }
    
    int ss = 0;
    
    ss |= d2;
    ss |= d4 << 1;
    ss |= d6 << 2;
    ss |= d8 << 3;

    return ss;
}

int decode(short st) {
    int res = 0;

    int s1 = st >> 8;
    int s2 = st;

    int s11 = decodeHelper(s1);
    int s22 = decodeHelper(s2);

    if (s11 != -1 && s22 != -1) {
        res = s11 * 16 + s22; 
    } else {
        res = -1;
    }
    
    return res;
}
