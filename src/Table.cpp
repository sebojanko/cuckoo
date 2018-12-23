//
// Created by Luka on 10/22/18.
//

#include <iostream>
#include "Table.h"

// čisto za debug
template <class T>
void print(std::list<T> v) {
    for (auto val : v) {
        std::cout << val << " ";
    }
}

Table::Table(Hasher *hasher, int b_size) {
    hasher_ = hasher;
    bucket_size = b_size;
    //table_ = {};
}

void Table::Insert(std::string element) {
    int iter = 0;
    int h = getHash(element);
    while (iter++ < 500) {
        table_[h].push_front(getFingerprint(h));
        return;
    }
}

void Table::Insert(int element) {
    int iter = 0;
    int h = getHash(element);
    while (iter++ < 500) {
        table_[h].push_front(getFingerprint(h));
        return;
    }
}

bool Table::Contains(std::string element) {
    size_t h = getHash(element);
    return std::find(table_[h].begin(), table_[h].end(), getFingerprint(h)) != table_[h].end();
}

bool Table::Contains(int element) {
    // TODO
}

bool Table::Remove(std::string element) {
    size_t h = getHash(element);
    std::list<int>::iterator it = std::find(table_[h].begin(), table_[h].end(), getFingerprint(h));
    if (it != table_[h].end()) {
        table_[h].erase(it);
        return true;
    }
    return false;
}

void Table::Print() {
    for (auto val : table_) {
        print(val.second);
        std::cout << std::endl;
    }
};

int Table::getFingerprint(std::string element) {
    return hasher_->fingerprint(element);
}
int Table::getFingerprint(size_t element) {
    return hasher_->fingerprint(element);
}
int Table::getHash(std::string element) {
    return hasher_->hash(element);
}

int Table::getHash(int element) {
    return hasher_->hash(element);
}
