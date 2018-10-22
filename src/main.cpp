//
// Created by sebo on 10/22/18.
//
#include <iostream>
#include "table.h"
#include <ctime>

int main() {

    Table table = Table();

    clock_t begin = clock();

    for (int i = 0; i < 10000000; i++) {
        table.Insert(i);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;



    std::cout << "Contains 43? - " << table.Contains(53) << std::endl;
    std::cout << "Elapsed: " << elapsed_secs << std::endl;

    return 0;
}