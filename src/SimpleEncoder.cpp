#include "SimpleEncoder.h"
#include <bitset>


SimpleEncoder::SimpleEncoder() {
    this->bits_per_char_ = 3;
}

SimpleEncoder::SimpleEncoder(size_t bits_per_char) {
    this->bits_per_char_ = bits_per_char;
}

uint64_t SimpleEncoder::encode(std::string item) {
    if (item.size() > (64 / bits_per_char_) - 1) {
        return 0ULL;
    }

    uint64_t encoded = (1ULL << (bits_per_char_ - 1));
    uint64_t enc_c;
    for (char& c : item) {
        if (c == 'A') {
            enc_c = 0ULL;
        } 
        else if (c == 'C') {
            enc_c = 1ULL;
        }
        else if (c == 'G') {
            enc_c = 2ULL;
        }
        else if (c == 'T') {
            enc_c = 3ULL;
        }

        encoded = (encoded << bits_per_char_) | enc_c;
    }

    return encoded;
}

std::string SimpleEncoder::decode(uint64_t encoded) {
    std::string item;

    uint64_t enc_c;
    
    while (true) {
        enc_c = encoded & ((1ULL << bits_per_char_) - 1);
        if (enc_c == (1ULL << (bits_per_char_ - 1))) {
            return item;
        }
        if (enc_c == 0ULL) {
            item.insert(0, 1, 'A');
        } 
        else if (enc_c == 1ULL) {
            item.insert(0, 1, 'C');
        }
        else if (enc_c == 2ULL) {
            item.insert(0, 1, 'G');
        }
        else if (enc_c == 3ULL) {
            item.insert(0, 1, 'T');
        }

        encoded = (encoded >> bits_per_char_);
    }

    return item;
}
