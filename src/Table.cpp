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
bool Table::Insert(T element) {
    unsigned long table_size = 8;
    uint16_t f = getFingerprint(element);
    uint64_t i1 = getHash(element);
    uint64_t i2 = i1 ^ getHash(f);

    if (table_[i1].size() < table_size) {
        table_[i1].push_front(f);
        return true;
    }
    if (table_[i2].size() < table_size) {
        table_[i2].push_front(f);
        return true;
    }

    int iter = 0;
    uint64_t i = (f % 2) ? i1 : i2;
    T elem;
    while (iter++ < 500) {
        elem = table_[i].back();
        table_[i].pop_back();
        table_[i].push_front(f);
        f = elem;
        i = i ^ getHash(f);
        if (table_[i].size() < table_size) {
            table_[i].push_front(f);
            return true;
        }
    }
    std::cout << "Filter full\n";
    return false;
}

template<class T>
bool Table::Contains(T element) {
    uint16_t f = getFingerprint(element);
    uint64_t i1 = getHash(element);
    uint64_t i2 = i1 ^ getHash(f);
    return
        std::find(table_[i1].begin(), table_[i1].end(), f) != table_[i1].end() ||
        std::find(table_[i2].begin(), table_[i2].end(), f) != table_[i2].end();
}

template<class T>
bool Table::Remove(T element) {
    uint16_t f = getFingerprint(element);
    uint64_t h = getHash(element);
    std::list<uint16_t>::iterator it = std::find(table_[h].begin(), table_[h].end(), f);
    if (it != table_[h].end()) {
        table_[h].erase(it);
        return true;
    }
    h = h ^ getHash(f);
    it = std::find(table_[h].begin(), table_[h].end(), f);
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
