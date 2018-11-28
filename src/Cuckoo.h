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

    void Insert(int element);

    bool Remove(int element);

    bool Contains(int element);

    void Print();

};

#endif //CUCKOO_CUCKOO_H
