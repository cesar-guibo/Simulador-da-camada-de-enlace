#include "errors.hpp"
#include <iostream>

Bit compute_even_parity(const std::vector<Bit> &frame)
{
    int counter = 0; 
    for (Bit bit : frame) {
        counter += bit;
    }
    return counter % 2 != 0;
}

Bit compute_odd_parity(const std::vector<Bit> &frame)
{
    return !compute_even_parity(frame);
}

int compute_crc(const std::vector<Bit> &dividend)
{
    std::vector<Bit> input(32, 0);
    input.insert(input.begin(), dividend.begin(), dividend.end());
    /* Generator CRC-32 that conforms to the IEEE 802 from Kurose | Ross */
    long generator = 0x0000000104C11DB7;
    long significant_bit_mask = 0x0000000100000000;

    /* Buffers the bints in a long variable to perform a single xor 
     * per step of the division. */
    long remainder = 0;
    for (int i = 0; i < input.size(); ++i) {
        remainder = (remainder << 1) | input[i];
        bool needs_xor = (remainder & generator) & significant_bit_mask;
        remainder ^= generator & (needs_xor ? generator :  0x0000000000000000);
    }
    return (int)remainder;
}
