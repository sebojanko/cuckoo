//
// Created by sebo on 11/28/18.
//

#ifndef CUCKOO_CUCKOO_H
#define CUCKOO_CUCKOO_H

#include <iostream>
#include "Table.h"
#include "Table.cpp"

class Cuckoo {
private:
    Table table_ = NULL;

public:
    Cuckoo();
    Cuckoo(HashType h, int fprint_size, int bucket_size, int num_of_buckets);

    template<class T>
    bool Insert(const T& element);

    template<class T>
    bool Remove(const T& element);

    template<class T>
    bool Contains(const T& element) const;

    void Print();

};

#endif //CUCKOO_CUCKOO_H
