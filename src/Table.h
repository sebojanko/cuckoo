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
#include "Hash.cpp"

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
    
    template<class T>
    uint64_t getHash(T& element);
    template<class T>
    uint16_t getFingerprint(T& element);

public:
    Table(Hasher *hasher, int bucket_size = 8);

    template<class T>
    bool Insert(T& element);

    template<class T>
    bool Remove(T& element);

    template<class T>
    bool Contains(T& element);

    void Print();

};

#endif //CUCKOO_TABLE_H
