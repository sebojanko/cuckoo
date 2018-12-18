#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <bitset>


class SimpleEncoder {
private:
    size_t bits_per_char_; // defaults to 3

public:
    SimpleEncoder();
    SimpleEncoder(size_t bits_per_char); // more or less useless

    uint64_t encode(std::string item);
    std::string decode(uint64_t encoded);

    // same as encode
    uint64_t operator()(std::string item);
};

#endif

