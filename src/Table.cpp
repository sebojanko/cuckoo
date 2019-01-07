//
// Created by Luka on 10/22/18.
//

#pragma once
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
bool Table::Insert(const T& element) {
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
    uint16_t elem;
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
    return false;
}

template<class T>
bool Table::Contains(const T& element) const {
    uint16_t f = getFingerprint(element);
    uint64_t i1 = getHash(element);

    auto it = table_.find(i1);
    bool myb = false;
    if (it != table_.end()) {
        myb |= std::find(it->second.begin(), it->second.end(), f) != it->second.end();
        if (myb) {
            return myb;
        }
    }
    uint64_t i2 = i1 ^ getHash(f);
    auto it2 = table_.find(i2);
    if (it2 != table_.end()) {
        myb |= std::find(it2->second.begin(), it2->second.end(), f) != it2->second.end();
    }
    return myb;
}

template<class T>
bool Table::Remove(const T& element) {
    uint16_t f = getFingerprint(element);
    uint64_t h = getHash(element);
    if (table_.count(h)) {
        std::list<uint16_t>::iterator it = std::find(table_[h].begin(), table_[h].end(), f);
        if (it != table_[h].end()) {
            table_[h].erase(it);
            return true;
        }
    }

    h = h ^ getHash(f);
    if (table_.count(h)) {
        std::list<uint16_t>::iterator it = std::find(table_[h].begin(), table_[h].end(), f);
        if (it != table_[h].end()) {
            table_[h].erase(it);
            return true;
        }
    }
    return false;
}

template<class T>
uint16_t Table::getFingerprint(const T& element) const {
    return hasher_->fingerprint(element);
}

template<class T>
uint64_t Table::getHash(const T& element) const {
    return hasher_->hash(element);
}
