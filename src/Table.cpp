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
        if (table_[h].size() < 8) {
            table_[getHash(element)].push_front(getFingerprint(element));
            return;
        } else {
            //magic
        }
    }
}

void Table::Insert(int element) {
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
    return std::find(table_[h].begin(), table_[h].end(), getFingerprint(element)) != table_[h].end();
}
bool Table::Contains(int element) {
    size_t h = getHash(element);
    if (table_.find(h) != table_.end()) {
        return table_[h].Contains(element);
    }
    return false;
}

bool Table::Remove(std::string element) {
    size_t h = getHash(element);
    table_[h].erase(std::find(table_[h].begin(), table_[h].end(), getFingerprint(element)));
    // trebam vidjeti kaj vraca
    return true;
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
int Table::getHash(std::string element) {
    return hasher_->hash(element);
}

int Table::getHash(int element) {
    return hasher_->hash(element);
}
