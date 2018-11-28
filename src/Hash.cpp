#include "Hash.h"

Hasher::Hasher(int bits_per_item) {
    this->bits_per_item_ = bits_per_item;
}

std::size_t Hasher::hash(std::string item) {
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


