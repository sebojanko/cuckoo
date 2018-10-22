//
// Created by sebo on 10/22/18.
//
#include <iostream>
#include "table.h"

int main() {
    Table table = Table();

    table.insert(11);
    table.insert(12);
    table.insert(8723);
    table.insert(34);
    table.insert(54);
    table.insert(4176);
    table.insert(43122);
    table.insert(343);
    table.insert(4457);
    table.insert(875);
    table.insert(31454);
    table.insert(476);
    table.insert(122);
    table.insert(43);
    table.insert(4757);
    table.insert(475);

    table.print();

    /*table.remove(1);

    for (int i : table) {
        std::cout << i << std:endl;
    }

    std::cout << "Contains 2? - " << table.contains(2) << std::endl;
*/
    return 0;
}