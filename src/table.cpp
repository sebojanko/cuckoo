//
// Created by sebo on 10/22/18.
//

#include <iostream>
#include "table.h"

void Table::Insert(int element) {
    int colHash = getColHash(element);
    int rowHash = getRowHash(element);
    table_[rowHash][colHash] = element;
}

bool Table::Contains(int element) {
    int colHash = getColHash(element);
    int rowHash = getRowHash(element);

    return table_[rowHash][colHash] == element;
}

bool Table::Remove(int element) {
    if (Contains(element)) {
        int colHash = getColHash(element);
        int rowHash = getRowHash(element);

        table_[rowHash][colHash] = 0;
        return true;
    }
    return false;
};

void Table::Print() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << table_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
};

int Table::getRowHash(int element) {
    int hash = static_cast<int>(std::hash<float>{}(element) / 100000000000000000);
    return hash;
}

int Table::getColHash(int element) {
    int hash = static_cast<int>(std::hash<float>{}(element) / 100000000000000000);
    return hash;
}
