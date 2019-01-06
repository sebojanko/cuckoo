#pragma once
#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <random>

#include <openssl/evp.h>

// Author: David (cizl)

// TIMS - Two independent multiply shift, Martin Dietzfelbinger,
// "Universal hashing and k-wise independent random
// variables via integer arithmetic without primes".
enum class Hash { STL, MD5, SHA1, TIMS, IDENTITY };// BOB_HASH, MURMUR_HASH};


class Hasher {
private:
    size_t bits_per_item_;
    Hash hash_function_;
    unsigned __int128 multiply_, add_;

public:
    Hasher(size_t bits_per_item);
    Hasher(size_t bits_per_item, Hash hash_function);

    uint64_t hash(std::string item);
    uint64_t hash(int item);

    // same as hash
    uint64_t operator()(std::string item);

    uint16_t fingerprint(std::string item);
    uint16_t fingerprint(uint64_t hash);

    uint64_t twoIndependentMultiplyShift(uint64_t item);
};


uint32_t stringToUint32(unsigned char *data);
uint64_t stringToUint64(unsigned char *data);


#endif

