#pragma once
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

    std::random_device random;
    for (auto v : {&multiply_, &add_}) {
        *v = random();
        for (int i = 1; i <= 4; ++i) {
            *v = *v << 32;
            *v |= random();
        }
    }
}

std::uint64_t Hasher::hash(uint64_t item) {
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
    if (this->hash_function_ == Hash::STL) {
        return std::hash<uint64_t>{}(item);  
    }

    // defaults to identity "hash"
    return item;
}

std::uint64_t Hasher::hash(std::string item) {
    if (this->hash_function_ == Hash::TIMS) {
        uint64_t enc = enc_.encode(item);
        return twoIndependentMultiplyShift(enc);
    }
    if (this->hash_function_ == Hash::MD5) {
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        MD5(charData, item.length(), (unsigned char*)&md);
        return stringToUint64(md);
    }
    if (this->hash_function_ == Hash::SHA1) {
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        SHA1(charData, item.length(), (unsigned char*)&md);
        return stringToUint64(md);
    }
    if (this->hash_function_ == Hash::STL) {
        return std::hash<std::string>{}(item);
    }

    // "identity hash" - encoded k-mer
    return enc_.encode(item);
}

std::uint16_t Hasher::fingerprint(uint64_t hash) {
    hash = hash & ((1ULL << bits_per_item_) - 1);
    //hash += (hash == 0);
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

uint64_t Hasher::twoIndependentMultiplyShift(uint64_t item) {
    return (add_ + multiply_ * static_cast<decltype(multiply_)>(item)) >> 64;
};
