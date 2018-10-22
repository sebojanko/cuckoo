//
// Created by sebo on 10/22/18.
//

#ifndef CUCKOO_TABLE_H
#define CUCKOO_TABLE_H

#include <array>

class Table {
private:
    static const int ROWS{1000};
    static const int COLS{1000};
    std::array<std::array<int, COLS>, ROWS> table_;

public:
    void Insert(int element);

    bool Remove(int element);

    bool Contains(int element);

    void Print();

    int getRowHash(int element);

    int getColHash(int element);
};

#endif //CUCKOO_TABLE_H
