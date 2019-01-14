//
// Created by Luka on 10/22/18.
//

#ifndef SRC_TABLE_H_
#define SRC_TABLE_H_

#include <iostream>
#include <iomanip>
#include <array>
#include <unordered_map>
#include <list>
#include <algorithm>

#include "Hash.h"
#include "Hash.cpp"

class Table {
 public:
    Table(Hasher *hasher, size_t bucket_size = 8,
          size_t num_of_buckets = 524288);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

 private:
    Hasher *hasher_;
    std::unordered_map<uint64_t, std::list<uint16_t>> table_;
    size_t bucket_size_;
    size_t num_of_buckets_;

    template<class T>
    uint64_t getHash(const T& element) const;
    template<class T>
    uint16_t getFingerprint(const T& element) const;
};

#endif  // SRC_TABLE_H_
