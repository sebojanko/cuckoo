#include "Hash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>


Hasher::Hasher(int bits_per_item) {
    this->bits_per_item_ = bits_per_item;
}

Hasher::Hasher(int bits_per_item, Hash hash_function) {
    this->bits_per_item_ = bits_per_item;
    this->hash_function_ = hash_function;
}

std::size_t Hasher::hash(std::string item) {
    if (this->hash_function_ == Hash::MD5) {
        unsigned char *md;
        int hashLen;
        md = MD5Hash(item, &hashLen);
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

unsigned char *MD5Hash(unsigned char *data, size_t dataLen, int *hashLen) {
    unsigned char *md = NULL;
    EVP_MD_CTX *ctx = NULL;
    const EVP_MD *mdType = EVP_md5();
    
    *hashLen = EVP_MD_size(mdType);
    
    md = (unsigned char *) malloc(*hashLen);
    ctx = EVP_MD_CTX_create();
    
    EVP_MD_CTX_init(ctx);
    EVP_DigestInit_ex(ctx, mdType, NULL);
    EVP_DigestUpdate(ctx, data, dataLen);
    EVP_DigestFinal_ex(ctx, md, NULL);
    //EVP_MD_CTX_cleanup(ctx);
    EVP_MD_CTX_reset(ctx); // replaces the line above
    EVP_MD_CTX_destroy(ctx);

    return md;
}

unsigned char *MD5Hash(std::string data, int *hashLen) {
    // cast from string to unsigned char*
    unsigned char *charData= (unsigned char*) data.c_str();
    return MD5Hash(charData, data.length(), hashLen);
}

std::string MD5Hash(unsigned char *data, size_t dataLen) {
    int hashLen;
    return std::string((char*)MD5Hash(data, dataLen, &hashLen));
}

std::string MD5Hash(std::string data) {
    unsigned char *charData= (unsigned char*) data.c_str();
    int hashLen;
    return std::string((char*)MD5Hash(data, &hashLen));
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
    char data[1024];
    unsigned char *md;
    int i = 0, hashLen = 0;
    
    memset(&data, 0, 1024);
    
    scanf("%s", data);
    md = MD5Hash((unsigned char *)data, strlen(data), &hashLen);
    for(i = 0; i < hashLen; i++) {
        printf("%02x",md[i]);
    } printf("\n");

    std::string s("abc");
    md = MD5Hash(s, &hashLen);
    for(i = 0; i < hashLen; i++) {
        printf("%02x",md[i]);
    } printf("\n");

    std::cout << stringToUint32(md) << std::endl;

    Hasher hasher(8, Hash::MD5);
    int x = hasher.hash("abc");
    std::cout << x << std::endl;

    return 0;
}
*/
