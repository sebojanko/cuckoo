//
// Created by sebo on 11/28/18.
//

#ifndef SRC_CUCKOO_H_
#define SRC_CUCKOO_H_

#include <math.h>

#include <iostream>

#include "CompactTable.h"
#include "CompactTable.cpp"
#include "Table.h"
#include "Table.cpp"

class Cuckoo {
 public:
    Cuckoo(HashType h, int fprint_size, int bucket_size, int max_num_elements);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

 private:
    // Table table_ = NULL;
    CompactTable table_ = NULL;
};

#endif  // SRC_CUCKOO_H_
