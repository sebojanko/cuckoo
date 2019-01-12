#pragma once
#ifndef HASH_H
#define HASH_H

#include <openssl/md5.h>
#include <openssl/sha.h>

#include <iostream>
#include <iomanip>
#include <random>
#include <string>

#include "SimpleEncoder.h"

// Author: David (cizl)

// available hash functions
// TIMS - Two independent multiply shift
enum class HashType { STL, MD5, SHA1, TIMS, IDENTITY };


// Hashes a string or a uint64_t into a uint64_t.
// Example:
//    Hasher hasher(8, Hash::SHA1);
//    uint64_t h1 = hasher.hash(123412341234ULL);
//    uint64_t h2 = hasher.hash("ACGTACGTACGT");
class Hasher {
 public:
    explicit Hasher(size_t bits_per_item);
    Hasher(size_t bits_per_item, HashType hash_function);

    // Hashes the specified string into a uint64_t.
    // If the TIMS or IDENTITY hash is chosen, the string
    // is first encoded into a 64bit unsigned integer.
    uint64_t Hash(std::string item);

    // Hashes the specified uint64_t into a uint64_t.
    // If the MD5 or SHA1 hash is chosen, the uint64_t
    // is first transformed into a string.
    uint64_t Hash(uint64_t item);

    // Same as hash.
    uint64_t operator()(std::string item);

    // Returns the last 'bits_per_item_' bits of the specified element.
    uint16_t Fingerprint(uint64_t hash);

    // Martin Dietzfelbinger, "Universal hashing and k-wise independent
    // random variables via integer arithmetic without primes".
    uint64_t TwoIndependentMultiplyShift(uint64_t item);

 private:
    size_t bits_per_item_;
    HashType hash_function_;
    unsigned __int128 multiply_, add_;
    SimpleEncoder enc_;
};

// Packs the first 4 characters of a string into a
// 32 bit unsigned integer.
uint32_t StringToUint32(unsigned char *data);

// Packs the first 4 characters of a string into a
// 64 bit unsigned integer.
uint64_t StringToUint64(unsigned char *data);


#endif

