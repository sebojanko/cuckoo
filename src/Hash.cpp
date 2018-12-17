#include "Hash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>


Hasher::Hasher(int bits_per_item) {
    this->bits_per_item_ = bits_per_item;
}

Hasher::Hasher(int bits_per_item, Hash hash_function) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = hash_function;
}

std::uint32_t Hasher::hash(int item) {
    std::string item_str = std::to_string(item);
    if (this->hash_function_ == Hash::MD5) {
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData= (unsigned char*) item_str.c_str();
        MD5(charData, item_str.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    if (this->hash_function_ == Hash::SHA1) {
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData= (unsigned char*) item_str.c_str();
        SHA1(charData, item_str.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    // TODO dodat ostale hasheve
    return std::hash<int>{}(item);
    
}

std::uint32_t Hasher::hash(std::string item) {
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
    return std::hash<std::string>{}(item);
}

std::uint32_t Hasher::operator()(std::string item) {
    return std::hash<std::string>{}(item);
}

std::uint16_t Hasher::fingerprint(std::string item) {
    uint32_t fp = hash(item);
    fp = fp & ((1ULL << bits_per_item_) - 1);
    fp += (fp == 0);
    return fp;
}

std::uint16_t Hasher::fingerprint(size_t hash) {
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
