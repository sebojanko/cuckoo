//
// Created by sebo on 10/22/18.
//

#include <iostream>
#include "Table.h"

Table::Table(Hasher *hasher) {
    hasher_ = hasher;
    //table_ = {};
}

void Table::Insert(int element) {
    int colHash = 0;
    int rowHash = 0;
    table_[rowHash][colHash] = element;
}

bool Table::Contains(int element) {
    int colHash = 0;
    int rowHash = 0;

    return table_[rowHash][colHash] == element;
}

bool Table::Remove(int element) {
    if (Contains(element)) {
        int colHash = 0;
        int rowHash = 0;

        table_[rowHash][colHash] = 0;
        return true;
    }
    return false;
}

void Table::Print() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << table_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
};

int Table::getHash(int element) {
    return hasher_->hash(element);
}
