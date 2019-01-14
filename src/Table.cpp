//
// Created by Luka on 10/22/18.
//

#pragma once
#include <assert.h>

#include "Table.h"

// čisto za debug
template <class T>
void print(std::list<T> v) {
    for (auto val : v) {
        std::cout << std::setw(6) << val;
    }
}

void Table::Print() {
    int filled = 0, total = 0;
    std::cout << "Table:\n";
    for (auto val : table_) {
        if (val.second.size() > 0) {
            std::cout << std::setw(8) << val.first << ": ";
            filled++;
            total += val.second.size();
        } else {
            continue;
        }
        print(val.second);
        std::cout << std::endl;
    }
}

Table::Table(Hasher *hasher, size_t b_size, size_t num_of_buckets) {
    hasher_ = hasher;
    bucket_size_ = b_size;
    num_of_buckets_ = num_of_buckets;
}

template<class T>
bool Table::Insert(const T& element) {
    uint64_t h = getHash(element);
    uint64_t i1 = (h >> 32) % num_of_buckets_;
    uint16_t f = getFingerprint(h);
    uint64_t i2 = (i1 ^ getHash(f)) % num_of_buckets_;

    // check if (alt index of i2) == i1
    assert(i1 == ((i2 ^ getHash(f)) % num_of_buckets_));

    if (table_[i1].size() < bucket_size_) {
        table_[i1].push_front(f);
        return true;
    }
    if (table_[i2].size() < bucket_size_) {
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
        i = (i ^ getHash(f)) % num_of_buckets_;
        if (table_[i].size() < bucket_size_) {
            table_[i].push_front(f);
            return true;
        }
    }
    return false;
}

template<class T>
bool Table::Contains(const T& element) const {
    uint64_t h = getHash(element);
    uint64_t i1 = (h >> 32) % num_of_buckets_;
    uint16_t f = getFingerprint(h);

    auto it = table_.find(i1);
    bool myb = false;
    if (it != table_.end()) {
        myb |= std::find(it->second.begin(), it->second.end(), f) != it->second.end();
        if (myb) {
            return myb;
        }
    }
    uint64_t i2 = (i1 ^ getHash(f)) % num_of_buckets_;
    auto it2 = table_.find(i2);
    if (it2 != table_.end()) {
        myb |= std::find(it2->second.begin(), it2->second.end(), f) != it2->second.end();
    }
    return myb;
}

template<class T>
bool Table::Remove(const T& element) {
    uint64_t h = getHash(element);
    uint64_t i1 = (h >> 32) % num_of_buckets_;
    uint16_t f = getFingerprint(h);

    if (table_.count(i1)) {
        std::list<uint16_t>::iterator it = std::find(table_[i1].begin(), table_[i1].end(), f);
        if (it != table_[i1].end()) {
            table_[i1].erase(it);
            return true;
        }
    }

    uint64_t i2 = (i1 ^ getHash(f)) % num_of_buckets_;
    if (table_.count(i2)) {
        std::list<uint16_t>::iterator it = std::find(table_[i2].begin(), table_[i2].end(), f);
        if (it != table_[i2].end()) {
            table_[i2].erase(it);
            return true;
        }
    }
    return false;
}

template<class T>
uint16_t Table::getFingerprint(const T& element) const {
    return hasher_->Fingerprint(element);
}

template<class T>
uint64_t Table::getHash(const T& element) const {
    return hasher_->Hash(element);
}
