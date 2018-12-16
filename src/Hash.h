#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <random>

#include <openssl/evp.h>


enum class Hash { DEFAULT, BOB_HASH, MURMUR_HASH, MD5, SHA1 };


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

};


uint32_t stringToUint32(unsigned char *data);
uint64_t stringToUint64(unsigned char *data);

#endif

