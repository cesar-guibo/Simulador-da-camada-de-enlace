#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "bits.hpp"
#include "errors.hpp"

const int ERROR_PROBABILITY = 5;
const int RANODM_SEED = 0x02F71CA8;

void receiver_application(const std::string &message)
{
    std::cout << "[Receiver] The received message was: "
        << message
        << std::endl
        << std::endl;
}

void receiver_application_layer(const std::vector<Bit> &frame)
{
    ErrorHandler error = (ErrorHandler)(frame[1] | (frame[0] << 1));
    bool has_error;
    int message_size;
    int message_start = 2;
    switch(error) {
        case EVEN_PARITY:
            has_error = compute_even_parity(frame);
            if (has_error) {
                std::cout << ERROR_MSGS[error] << std::endl;;
            }
            /* Removes the parity bit and the error detection
             * type bits form the frame size to calculate the 
             * message size. */
            message_size = frame.size() - 2;
            break;
        case ODD_PARITY:
            has_error = compute_odd_parity(frame);
            if (has_error) {
                std::cout << ERROR_MSGS[error] << std::endl;;
            }
            /* Removes the parity bit and the error detection
             * type bits form the frame size to calculate the 
             * message size. */
            message_size = frame.size() - 3;
            break;
        case CRC:
            has_error = compute_crc(frame);
            if (has_error) {
                std::cout << ERROR_MSGS[error] << std::endl;;
            }
            /* Removes the error detection type bits and the CRC polynomial
             * form the frame size to calculate the message size. */
            message_size = frame.size() - CRC_REMAINDER_SIZE - 2;
            break;
    }
    std::string message = bits_to_string(frame, message_start, message_size);
    receiver_application(message);
}

void communication_meddium(const std::vector<Bit> &frame)
{
    short number_of_errors = 0;
    short transmited_bit = 0;
    std::vector<Bit> output_frame(frame.size(), 0);
    for (short i = 0; i < frame.size(); ++i) {
        Bit error = std::rand() % 1000 < ERROR_PROBABILITY;
        output_frame[i] = frame[i] ^ error;
    }
    receiver_application_layer(output_frame);
}

void sender_application_layer(const std::string &message, ErrorHandler error)
{
    std::vector<Bit> frame = {
        (Bit)((error & 0x00000002) != 0),
        (Bit)((error & 0x00000001) != 0),
    };
    std::vector<Bit> message_bits = string_to_bits(message);
    frame.insert(frame.end(), message_bits.begin(), message_bits.end());
    switch(error) {
        case EVEN_PARITY:
            frame.push_back(compute_even_parity(frame));
            break;
        case ODD_PARITY:
            frame.push_back(compute_odd_parity(frame));
            break;
        case CRC:
            std::vector<Bit> remainder = int_to_bits(compute_crc(frame));
            frame.insert(frame.end(), remainder.begin(), remainder.end());
            break;
    }
    communication_meddium(frame);
    //receiver_application_layer(frame);
}

void sender_application(ErrorHandler error)
{
    std::string message = "This is the test message being used.";
    std::cout << "[Sender] Sending message: " << message << std::endl;
    sender_application_layer(message, error);
}

int main(void) {
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "SIMULATION FOR EVEN PARITY ERROR DETECTION" << std::endl;
    std::cout << "--------------------------------------------------"
        << std::endl
        << std::endl;
    std::srand(RANODM_SEED);
    for (int i = 0; i < 10; i++) {
        sender_application(EVEN_PARITY);
    }
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "SIMULATION FOR ODD PARITY ERROR DETECTION" << std::endl;
    std::cout << "--------------------------------------------------"
        << std::endl
        << std::endl;
    std::srand(RANODM_SEED);
    for (int i = 0; i < 10; i++) {
        sender_application(ODD_PARITY);
    }
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "SIMULATION FOR CRC ERROR DETECTION" << std::endl;
    std::cout << "--------------------------------------------------"
        << std::endl
        << std::endl;
    std::srand(RANODM_SEED);
    for (int i = 0; i < 10; i++) {
        sender_application(CRC);
    }
}
