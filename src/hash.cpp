#include "hash.h"

Hasher::Hasher(int bits_per_item) {
    this->bits_per_item = bits_per_item;
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
    fp = fp & ((1ULL << bits_per_item) - 1);
    fp += (fp == 0);
    return fp;
}

std::size_t Hasher::fingerprint(int item) {
    uint32_t fp = hash(item);
    fp = fp & ((1ULL << bits_per_item) - 1);
    fp += (fp == 0);
    return fp;
}


int main() {
    // demo
    Hasher hasher(8);

    std::string s1("abc"), s2("abd");

    // lol
    std::cout << std::setw(22) << s1 
              << std::setw(22) << s2 
              << std::endl;
    std::cout << std::setw(22) << hasher(s1) 
              << std::setw(22) << hasher(s2) 
              << std::endl;
    std::cout << std::setw(22) << hasher.hash(s1) 
              << std::setw(22) << hasher.hash(s2) 
              << std::endl;
    std::cout << std::setw(22) << hasher.fingerprint(s1) 
              << std::setw(22) << hasher.fingerprint(s2) 
              << std::endl;
}


