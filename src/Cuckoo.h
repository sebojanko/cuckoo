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

    void Insert(std::string element);

    bool Remove(std::string element);

    bool Contains(std::string element);

    void Print();

};

#endif //CUCKOO_CUCKOO_H
