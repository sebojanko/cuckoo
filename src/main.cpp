//
// Created by sebo on 10/22/18.
//
#include <iostream>
#include "table.h"
#include "FastADocument.h"
#include <ctime>


//TODO: samo jedan hash po itemu --> Sebo
//TODO: pogledati ASP hash tablicu --> Sebo
//TODO: istraziti fingerprintanje --> Sebo
//TODO: klasa hash i random izbori --> David
//TODO: klasa prima enum i vrati hash --> David
//TODO: cuckoo klasa --> Luka
//TODO: research data, FASTA --> Luka
int main() {

    Table table = Table();

    clock_t begin = clock();

    for (int i = 0; i < 10000000; i++) {
        break;
        table.Insert(i);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    FastADocument file("/home/mark/workspace/gits/cuckoo/ecoli.fa");

    std::cout << "Contains 43? - " << table.Contains(43) << std::endl;
    std::cout << "Elapsed: " << elapsed_secs << std::endl;

    //std::cout << file.GetFileName() << std::endl;
    //std::cout << file.GetNextSequence() << std::endl;
    return 0;
}
