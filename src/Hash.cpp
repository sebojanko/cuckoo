#include "Hash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

// Author: David (cizl)

Hasher::Hasher(size_t bits_per_item) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = Hash::STL;
}

Hasher::Hasher(size_t bits_per_item, Hash hash_function) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = hash_function;
}

std::uint64_t Hasher::hash(int item) {
    if (this->hash_function_ == Hash::TIMS) {
        return twoIndependentMultiplyShift(item);
    }
    if (this->hash_function_ == Hash::MD5) {
        std::string item_str = std::to_string(item);
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData= (unsigned char*) item_str.c_str();
        MD5(charData, item_str.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    if (this->hash_function_ == Hash::SHA1) {
        std::string item_str = std::to_string(item);
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData= (unsigned char*) item_str.c_str();
        SHA1(charData, item_str.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    if (this->hash_function_ == Hash::IDENTITY) {
        return item;
    }
    // TODO dodat ostale hasheve
    if (this->hash_function_ == Hash::STL) {
        return std::hash<int>{}(item);  
    }
}

std::uint64_t Hasher::hash(std::string item) {
    if (this->hash_function_ == Hash::MD5) {
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        MD5(charData, item.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    if (this->hash_function_ == Hash::SHA1) {
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        SHA1(charData, item.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    if (this->hash_function_ == Hash::STL) {
        return std::hash<std::string>{}(item);
    }
}

std::uint64_t Hasher::operator()(std::string item) {
    return std::hash<std::string>{}(item);
}

std::uint16_t Hasher::fingerprint(std::string item) {
    uint64_t fp = hash(item);
    fp = fp & ((1ULL << bits_per_item_) - 1);
    fp += (fp == 0);
    return fp;
}

std::uint16_t Hasher::fingerprint(uint64_t hash) {
    hash = hash & ((1ULL << bits_per_item_) - 1);
    hash += (hash == 0);
    return hash;
}

uint32_t stringToUint32(unsigned char *data) {
    uint32_t fingerprint = 0;
    for (int i = 0; i < 4; i++) {
        fingerprint |= (unsigned char) data[i] << (24 - i * 8);
    }
    return fingerprint;
}

uint64_t stringToUint64(unsigned char *data) {
    uint64_t fingerprint = 0;
    for (int i = 0; i < 8; i++) {
        fingerprint |= (unsigned char) data[i] << (56 - i * 8);
    }
    return fingerprint;
}

uint64_t twoIndependentMultiplyShift(uint64_t item) {
    unsigned __int128 multiply, add;
    std::random_device random;
    for (auto v : {&multiply, &add}) {
        *v = random();
        for (int i = 1; i <= 4; ++i) {
            *v = *v << 32;
            *v |= random();
        }
    }

    return (add + multiply * static_cast<decltype(multiply)>(item)) >> 64;
};
