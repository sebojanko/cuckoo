#pragma once
#include "Hash.h"


// Author: David (cizl)

Hasher::Hasher(const Hasher& other) {
    bits_per_item_ = other.bits_per_item_;
    hash_function_ = other.hash_function_;
    multiply_ = other.multiply_;
    add_ = other.add_;
    enc_ = other.enc_;
}

Hasher::Hasher(size_t bits_per_item) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = HashType::STL;
}

Hasher::Hasher(size_t bits_per_item, HashType hash_function) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = hash_function;

    // initialize variables for TIMS hash
    std::random_device random;
    for (auto v : {&multiply_, &add_}) {
        *v = random();
        for (int i = 1; i <= 4; ++i) {
            *v = *v << 32;
            *v |= random();
        }
    }
}

uint64_t Hasher::Hash(const uint64_t item) const {
    if (this->hash_function_ == HashType::TIMS) {
        return TwoIndependentMultiplyShift(item);
    }
    if (this->hash_function_ == HashType::MD5) {
        std::string item_str = std::to_string(item);
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item_str.c_str();
        MD5(charData, item_str.length(), (unsigned char*)&md);
        return StringToUint64(md);
    }
    if (this->hash_function_ == HashType::SHA1) {
        std::string item_str = std::to_string(item);
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item_str.c_str();
        SHA1(charData, item_str.length(), (unsigned char*)&md);
        return StringToUint64(md);
    }
    if (this->hash_function_ == HashType::STL) {
        return std::hash<uint64_t>{}(item);
    }

    // defaults to identity "hash"
    return item;
}

uint64_t Hasher::Hash(const std::string& item) const {
    if (this->hash_function_ == HashType::TIMS) {
        uint64_t enc = enc_.Encode(item);
        return TwoIndependentMultiplyShift(enc);
    }
    if (this->hash_function_ == HashType::MD5) {
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        MD5(charData, item.length(), (unsigned char*)&md);
        return StringToUint64(md);
    }
    if (this->hash_function_ == HashType::SHA1) {
        unsigned char md[SHA_DIGEST_LENGTH];
        unsigned char *charData = (unsigned char*) item.c_str();
        SHA1(charData, item.length(), (unsigned char*)&md);
        return StringToUint64(md);
    }
    if (this->hash_function_ == HashType::STL) {
        return std::hash<std::string>{}(item);
    }

    // "identity hash" for strings - encoded k-mer
    return enc_.Encode(item);
}

uint16_t Hasher::Fingerprint(uint64_t hash) const {
    // takes the last few bits of a hash by masking it
    //     hash & 000..00011111111
    hash = hash & ((1ULL << bits_per_item_) - 1);
    hash += (hash == 0);
    return hash;
}

uint64_t Hasher::TwoIndependentMultiplyShift(uint64_t item) const {
    return (add_ + multiply_ * static_cast<decltype(multiply_)>(item)) >> 64;
}

uint32_t StringToUint32(unsigned char *data) {
    uint32_t fingerprint = 0;
    for (int i = 0; i < 4; i++) {
        fingerprint |= (unsigned char) data[i] << (24 - i * 8);
    }
    return fingerprint;
}

uint64_t StringToUint64(unsigned char *data) {
    uint64_t fingerprint = 0;
    for (int i = 0; i < 8; i++) {
        fingerprint |= ((uint64_t) data[i]) << (56 - i * 8);
    }
    return fingerprint;
}
