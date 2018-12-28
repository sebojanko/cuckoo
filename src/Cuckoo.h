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
    Cuckoo(Hash h);

    template<class T>
    bool Insert(T& element);

    template<class T>
    bool Remove(T& element);

    template<class T>
    bool Contains(T& element);

    void Print();

};

#endif //CUCKOO_CUCKOO_H
