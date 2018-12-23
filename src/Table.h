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
    std::unordered_map<int, std::list<int>> table_;
    //static const int ROWS{1000};
    //static const int COLS{1000};
    //int table_[ROWS][COLS]{};
    int bucket_size;
    uint16_t getFingerprint(std::string element);
    uint16_t getFingerprint(uint64_t element);

    uint32_t getHash(std::string element);
    uint32_t getHash(uint64_t element);

public:
    Table(Hasher *hasher, int bucket_size = 8);

    void Insert(std::string element);
    void Insert(uint64_t element);

    bool Remove(std::string element);
    bool Remove(uint64_t element);

    bool Contains(std::string element);
    bool Contains(uint64_t element);

    void Print();

};

#endif //CUCKOO_TABLE_H
