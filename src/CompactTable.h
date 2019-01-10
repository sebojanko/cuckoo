//
// Created by David on 12/23/18.
//

#ifndef COMPACT_TABLE_H
#define COMPACT_TABLE_H

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>

#include "Hash.h"

class CompactTable {
private:
    Hasher *hasher_;
    uint16_t *table_;
    size_t bucket_size_;
    size_t bucket_count_;
    int max_num_kicks_;

    uint64_t getHashIndex(uint64_t hash);

public:
    CompactTable(Hasher *hasher, int bucket_size = 8, int bucket_count = 200000);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element);

    void Print();

};

#endif
