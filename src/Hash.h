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

    std::size_t hash(std::string item);
    std::size_t hash(int item);

    // same as hash
    std::size_t operator()(std::string item);
    std::size_t operator()(int item);

    size_t fingerprint(std::string item);
    size_t fingerprint(int item);

//    static uint32_t MurmurHash2(const void * key, int len, unsigned int seed);
//    static uint32_t MurmurHash2(std::string &key, unsigned int seed);
};


unsigned char *MD5Hash(std::string, int *hashLen);
//unsigned char *MD5Hash(unsigned char *data, size_t dataLen);
uint32_t stringToUint32(unsigned char *data);
uint64_t stringToUint64(unsigned char *data);

#endif

