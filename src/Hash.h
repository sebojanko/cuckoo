#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <random>

#include <openssl/evp.h>


// TIMS - Two independent multiply shift, Martin Dietzfelbinger,
// "Universal hashing and k-wise independent random
// variables via integer arithmetic without primes".
enum class Hash { STL, MD5, SHA1, TIMS, IDENTITY };// BOB_HASH, MURMUR_HASH};


class Hasher {
private:
    int bits_per_item_;
    Hash hash_function_;

public:
    Hasher(int bits_per_item);
    Hasher(int bits_per_item, Hash hash_function);

    uint32_t hash(std::string item);
    uint32_t hash(int item);

    // same as hash
    uint32_t operator()(std::string item);

    uint16_t fingerprint(std::string item);
    uint16_t fingerprint(size_t item);

};


uint32_t stringToUint32(unsigned char *data);
uint64_t stringToUint64(unsigned char *data);

uint64_t twoIndependentMultiplyShift(uint64_t item);

#endif

