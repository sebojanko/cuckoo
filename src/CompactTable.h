//
// Created by David on 12/23/18.
//

#ifndef SRC_COMPACTTABLE_H_
#define SRC_COMPACTTABLE_H_

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>

#include "Hash.h"
#include "Hash.cpp"


// The internal data structure of the Cuckoo filter.
// Uses a single large uint16_t array for storing fingerprints.
class CompactTable {
 public:
    CompactTable(Hasher *hasher, size_t bucket_size = 8,
                 size_t bucket_count = 524288);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

 private:
    Hasher *hasher_;
    uint16_t *table_;
    size_t bucket_size_;
    size_t bucket_count_;
    int max_num_kicks_;

    bool RemoveFingerprint(uint64_t bucket_index, uint16_t fp);
};

#endif  // SRC_COMPACTTABLE_H_
