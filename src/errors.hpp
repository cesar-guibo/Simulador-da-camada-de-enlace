#ifndef ERRORS_H
#define ERRORS_H

#include <vector>
#include "bits.hpp"

typedef enum { EVEN_PARITY=0, ODD_PARITY, CRC } ErrorHandler;

const std::vector<std::string> ERROR_MSGS = {
    "[Error] Corrupted message detected through even bit parity.",
    "[Error] Corrupted message detected through odd bit parity.",
    "[Error] Corrupted message detected through crc."
};

const int CRC_REMAINDER_SIZE = 32;

/* Receives a frame and returns its even parity bit */
Bit compute_even_parity(const std::vector<Bit> &frame);

/* Receives a frame and returns its odd parity bit */
Bit compute_odd_parity(const std::vector<Bit> &frame);

/* Receives a frame and returns its CRC-32 polynomial remainder as an integer */
int compute_crc(const std::vector<Bit> &dividend);

#endif
