//
// Created by Luka on 10/22/18.
//

#ifndef CUCKOO_TABLE_H
#define CUCKOO_TABLE_H

#include <array>
#include <unordered_map>
#include <list>
#include <algorithm>
#include "Hash.h"

class Table {
private:
    Hasher *hasher_;
    // TODO trebat ce ipak ovdje ubaciti 2D polje izgleda
    //std::map<std::string, Bucket*> table_;
    std::unordered_map<uint64_t, std::list<uint16_t>> table_;
    //static const int ROWS{1000};
    //static const int COLS{1000};
    //int table_[ROWS][COLS]{};
    int bucket_size;
    uint64_t getHash(std::string element);
    uint64_t getHash(int element);
    uint16_t getFingerprint(std::string element);
    uint16_t getFingerprint(uint64_t element);

public:
    Table(Hasher *hasher, int bucket_size = 8);

    void Insert(std::string element);
    void Insert(int element);

    bool Remove(std::string element);
    bool Remove(int element);

    bool Contains(std::string element);
    bool Contains(int element);

    void Print();

};

#endif //CUCKOO_TABLE_H
