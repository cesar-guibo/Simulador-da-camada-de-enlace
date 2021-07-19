#ifndef BITS_H
#define BITS_H

#include <vector>
#include <string>

typedef bool Bit;

/* Converts a string to a vector of bits. */
std::vector<Bit> string_to_bits(const std::string &message);

/* Converts a section of a vector of bits to a string. 
 * Recieves the offset of the start of the section and the size of the 
 * section. */
std::string bits_to_string(std::vector<Bit> bits, int start, int size);

/* Converts an integer to a vector of bits. */
std::vector<Bit> int_to_bits(int value);

#endif
