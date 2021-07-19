#include "bits.hpp"
#include <iostream>

static const short BYTE_SIZE = 8;

std::string bits_to_string(std::vector<Bit> bits, int start, int size)
{
    std::string str;
    int string_size = size / BYTE_SIZE;
    for (int i = 0; i < string_size; ++i) {
        char ch = 0x00;
        int byte_offset = i * BYTE_SIZE + start;
        for (int j = 0; j < BYTE_SIZE; ++j) {
            ch <<= 1;
            ch |= bits[byte_offset + j];
        }
        str.push_back(ch);
    }
    return str;
}

std::vector<Bit> string_to_bits(const std::string &message)
{
    std::vector<Bit> bits;
    for (int i = 0; i < message.size(); ++i) {
        unsigned char mask = 0x80;
        int current_byte = i * BYTE_SIZE;
        for (int j = 0; j < BYTE_SIZE; ++j) {
            bits.push_back((message[i] & mask) != 0);
            mask >>= 1;
        }
    }
    return bits;
}

std::vector<Bit> int_to_bits(int value)
{
    int n_bits = sizeof(int) * 8;
    std::vector<Bit> bits;
    unsigned mask = 0x80000000;
    for (int i = 0; i < n_bits; ++i) {
        bits.push_back((value & mask) != 0);
        mask >>= 1;
    }
    return bits;
}
