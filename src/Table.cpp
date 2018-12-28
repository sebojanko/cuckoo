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

void Table::Print() {
    for (auto val : table_) {
        print(val.second);
        std::cout << std::endl;
    }
}

Table::Table(Hasher *hasher, int b_size) {
    hasher_ = hasher;
    bucket_size = b_size;
    //table_ = {};
}

template<class T>
bool Table::Insert(T& element) {
    int iter = 0;
    while (iter++ < 500) {
        uint16_t f = getFingerprint(element);
        uint64_t i1 = getHash(element);
        uint64_t i2 = i1 ^ getHash(f);
        if (table_[i1].size() < 8) {
            table_[i1].push_front(f);
            return true;
        } else if (table_[i2].size() < 8) {
            table_[i2].push_front(f);
            return true;
        } else {
            table_[i1].push_front(f);
            element = table_[i1].back();
            table_[i1].pop_back();
        }
    }
    return false;
}

template<class T>
bool Table::Contains(T& element) {
    uint64_t h = getHash(element);
    return std::find(table_[h].begin(), table_[h].end(), getFingerprint(h)) != table_[h].end();
}

template<class T>
bool Table::Remove(T& element) {
    uint64_t h = getHash(element);
    std::list<uint16_t>::iterator it = std::find(table_[h].begin(), table_[h].end(), getFingerprint(h));
    if (it != table_[h].end()) {
        table_[h].erase(it);
        return true;
    }
    return false;
}

template<class T>
uint16_t Table::getFingerprint(T& element) {
    return hasher_->fingerprint(element);
}

template<class T>
uint64_t Table::getHash(T& element) {
    return hasher_->hash(element);
}
