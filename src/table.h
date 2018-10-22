//
// Created by sebo on 10/22/18.
//

#ifndef CUCKOO_TABLE_H
#define CUCKOO_TABLE_H

#include <array>

class Table {
private:
    std::array<std::array<int, 4>, 8> table;
    std::array<int, 8> index;

public:
    void insert(int element);

    bool remove(int element);

    bool contains(int element);

    void print();
};

#endif //CUCKOO_TABLE_H
