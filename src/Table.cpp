//
// Created by sebo on 10/22/18.
//

#include <iostream>
#include "Table.h"

Table::Table(Hasher *hasher) {
    hasher_ = hasher;
    table_ = {};
}

void Table::Insert(std::string element) {
    size_t h = getHash(element);
    if (table_.find(h) != table_.end()) {
        table_[h].Push(element);
    } else {
        table_[h] = Bucket();
        table_[h].Push(element);
    }
}

bool Table::Contains(std::string element) {
    size_t h = getHash(element);
    if (table_.find(h) != table_.end()) {
        return table_[h].Contains(element);
    }
    return false;
}

bool Table::Remove(std::string element) {
    size_t h = getHash(element);
    if (table_.find(h) != table_.end()) {
        return table_[h].Remove(element);
    }
    return false;
}

void Table::Print() {
    for (auto v : table_) {
        v.second.print();
        std::cout << std::endl;
    }
};

int Table::getHash(std::string element) {
    return hasher_->hash(element);
}
