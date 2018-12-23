//
// Created by sebo on 11/28/18.
//

#ifndef CUCKOO_CUCKOO_H
#define CUCKOO_CUCKOO_H

#include "Table.h"

class Cuckoo {
private:
    Table table_ = NULL;

public:
    Cuckoo();
    Cuckoo(Hash h);

    void Insert(std::string element);
    void Insert(uint64_t element);

    bool Remove(std::string element);
    bool Remove(uint64_t element);

    bool Contains(std::string element);
    bool Contains(uint64_t element);

    void Print();

};

#endif //CUCKOO_CUCKOO_H
