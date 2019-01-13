//
// Created by sebo on 11/28/18.
//

#ifndef CUCKOO_CUCKOO_H
#define CUCKOO_CUCKOO_H

#include <iostream>
#include <math.h>
#include "CompactTable.h"
#include "CompactTable.cpp"

class Cuckoo {
private:
    CompactTable table_ = NULL;

public:
    Cuckoo();
    Cuckoo(HashType h, int fprint_size, int bucket_size, int max_num_elements);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

};

#endif //CUCKOO_CUCKOO_H
