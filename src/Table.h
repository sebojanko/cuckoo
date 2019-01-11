//
// Created by Luka on 10/22/18.
//

#ifndef CUCKOO_TABLE_H
#define CUCKOO_TABLE_H

#include <array>
#include <unordered_map>
#include <list>
#include <algorithm>
#include "Hash.h"
#include "Hash.cpp"

class Table {
private:
    Hasher *hasher_;
    std::unordered_map<uint64_t, std::list<uint16_t>> table_;
    // cisto da se kompajler ne buni zbog usporedbe .size() i inta
    unsigned long bucket_size_;
    int num_of_buckets_;
    
    template<class T>
    uint64_t getHash(const T& element) const;
    template<class T>
    uint16_t getFingerprint(const T& element) const;

public:
    Table(Hasher *hasher, int bucket_size = 8, int num_of_buckets = 128000);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

};

#endif //CUCKOO_TABLE_H
