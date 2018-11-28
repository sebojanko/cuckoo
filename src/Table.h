//
// Created by sebo on 10/22/18.
//

#ifndef CUCKOO_TABLE_H
#define CUCKOO_TABLE_H

#include <array>
#include <map>
#include "Bucket.h"
#include "Hash.h"

class Table {
private:
    Hasher *hasher_;
    // TODO trebat ce ipak ovdje ubaciti 2D polje izgleda
    //std::map<std::string, Bucket*> table_;
    //std::map<int, Bucket*> table_;
    static const int ROWS{1000};
    static const int COLS{1000};
    int table_[ROWS][COLS]{};
    int getHash(int element);

public:
    Table(Hasher *hasher);

    void Insert(int element);

    bool Remove(int element);

    bool Contains(int element);

    void Print();

};

#endif //CUCKOO_TABLE_H
