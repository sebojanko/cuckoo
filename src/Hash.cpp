#include "Hash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>


Hasher::Hasher(int bits_per_item) {
    this->bits_per_item_ = bits_per_item;
}

Hasher::Hasher(int bits_per_item, Hash hash_function) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = hash_function;
}

std::size_t Hasher::hash(std::string item) {
    if (this->hash_function_ == Hash::MD5) {
        unsigned char md[MD5_DIGEST_LENGTH];
        unsigned char *charData= (unsigned char*) item.c_str();
        MD5(charData, item.length(), (unsigned char*)&md);
        return stringToUint32(md);
    }
    return std::hash<std::string>{}(item);
}

std::size_t Hasher::hash(int item) {
    return std::hash<int>{}(item);
}

std::size_t Hasher::operator()(std::string item) {
    return std::hash<std::string>{}(item);
}

std::size_t Hasher::operator()(int item) {
    return std::hash<int>{}(item);
}

std::size_t Hasher::fingerprint(std::string item) {
    uint32_t fp = hash(item);
    fp = fp & ((1ULL << bits_per_item_) - 1);
    fp += (fp == 0);
    return fp;
}

std::size_t Hasher::fingerprint(int item) {
    uint32_t fp = hash(item);
    fp = fp & ((1ULL << bits_per_item_) - 1);
    fp += (fp == 0);
    return fp;
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


/*
int main() {

    std::string item("abc");
    unsigned char md[MD5_DIGEST_LENGTH];
    int hashLen;
    //md = MD5Hash(item, &hashLen);
    unsigned char *charData= (unsigned char*) item.c_str();
    MD5(charData, item.length(), (unsigned char*)&md);
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x",md[i]);
    } printf("\n");

    return 0;
}
*/
