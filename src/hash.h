#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <random>


class Hasher {
private:
    int bits_per_item;

public:
    Hasher(int bits_per_item);

    std::size_t hash(std::string item);
    std::size_t hash(int item);

    // same as hash
    std::size_t operator()(std::string item);
    std::size_t operator()(int item);

    size_t fingerprint(std::string item);
    size_t fingerprint(int item);

};

#endif
