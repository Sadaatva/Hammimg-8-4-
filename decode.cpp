#include <iostream>
#include <bitset>

char decodeHelper(char s){
    std::bitset<8> bits(s);
 
    bool d1 = bits[0], d2 = bits[1], d3 = bits[2], d4 = bits[3];
    bool d5 = bits[4], d6 = bits[5], d7 = bits[6], d8 = bits[7];

    bool A = (d1 + d2 + d6 + d8) % 2 == 1;
    bool B = (d2 + d3 + d4 + d8) % 2 == 1;
    bool C = (d2 + d4 + d5 + d6) % 2 == 1;
    bool D = (d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8) % 2 == 1;

    if (A && B && C && D) {
        return s;
    } else if (A && B && C && !D) {
        std::cout << "Error in p4, correcting, but accepting packet.\n";
        bits.flip(7);
        return static_cast<char>(bits.to_ulong());
    } else if ((!A || !B || !C) && D) {
        std::cout << "Single error\n";
        if (!A) bits.flip(0); 
        if (!B) bits.flip(1); 
        if (!C) bits.flip(3); 
        return static_cast<char>(bits.to_ulong());
    } else {
        std::cout << "Double error, rejecting packet.\n";
        return '\0'; 
    }
}

bool decode(unsigned short s) {
    char s1 = s >> 8;
    char s2 = static_cast<char>(s);

    char decoded_s1 = decodeHelper(s1);
    char decoded_s2 = decodeHelper(s2);

    if (decoded_s1 == '\0' || decoded_s2 == '\0') {
        std::cout << "Error in decoding\n";
        return false;
    } else {
        int r = (decoded_s1 << 8) | decoded_s2;
        std::cout << "Decoded value: " << r << '\n';
        return true;
    }
}

int main() {
    unsigned short example = 0b11011000;
    bool res = decode(example);
    
    if (!res) {
        std::cout << "Decoding failed.\n";
    }

    return 0;
}
