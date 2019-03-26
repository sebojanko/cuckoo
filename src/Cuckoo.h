//
// Created by sebo on 11/28/18.
//

#pragma once
#include <math.h>

#include <iostream>

#include "CompactTable.h"
#include "CompactTable.cpp"
#include "Table.h"
#include "Table.cpp"

class Cuckoo {
 public:
    Cuckoo(HashType h, int fprint_size, int bucket_size, int max_num_elements);
    Cuckoo() = default;

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

 private:
    // Table table_ = NULL;
    CompactTable table_;
};
