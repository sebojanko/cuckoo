#include "SimpleEncoder.h"

// created by David on 18/12/18

uint64_t SimpleEncoder::Encode(const std::string& item) const {
    int k = (64 / bits_per_char_) - 1;
    std::string new_item(item);
    if (item.size() > (64 / bits_per_char_) - 1) {
        new_item.resize(k);
    }

    // set delimiter first (0..0100)
    uint64_t encoded = (1ULL << (bits_per_char_ - 1));
    uint64_t enc_c = 0ULL;
    for (const char& c : new_item) {
        if (c == 'A') {
            enc_c = 0ULL;
        } else if (c == 'C') {
            enc_c = 1ULL;
        } else if (c == 'G') {
            enc_c = 2ULL;
        } else if (c == 'T') {
            enc_c = 3ULL;
        }

        // shift encoding left then add encoded char
        encoded = (encoded << bits_per_char_) | enc_c;
    }

    return encoded;
}

std::string SimpleEncoder::Decode(uint64_t encoded) {
    std::string item;

    uint64_t enc_c;

    while (true) {
        // get the encoded character -- the last few bits
        enc_c = encoded & ((1ULL << bits_per_char_) - 1);

        // finish when encoding == delimiter
        if (enc_c == (1ULL << (bits_per_char_ - 1))) {
            return item;
        }
        if (enc_c == 0ULL) {
            item.insert(0, 1, 'A');
        } else if (enc_c == 1ULL) {
            item.insert(0, 1, 'C');
        } else if (enc_c == 2ULL) {
            item.insert(0, 1, 'G');
        } else if (enc_c == 3ULL) {
            item.insert(0, 1, 'T');
        }

        // prepare next character
        encoded = (encoded >> bits_per_char_);
    }

    return item;
}
