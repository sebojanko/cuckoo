//
// Created by sebo on 10/22/18.
//
#include <iostream>
#include "Table.h"
#include "Bucket.h"
#include "FastADocument.h"
#include "Hash.h"
#include <ctime>


//TODO: klasa hash i random izbori --> David
//TODO: klasa prima enum i vrati hash --> David
//TODO: cuckoo klasa --> Luka
//TODO: research data, FASTA --> Luka
int main() {

    Hasher hasher(8);
    Table table = Table(&hasher);

    clock_t begin = clock();

    for (int i = 0; i < 10000000; i++) {
        break;
        table.Insert(i);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    Bucket buck("bokic");
    buck.Push("kaksi");
    //FastADocument file("/home/sebo/Documents/MojiProjekti/Cpp/cuckoo/ecoli.fa");
    //std::cout << file.GetNextSequence() << std::endl;

    buck.print();
    // demo

    std::string s1("abc"), s2("abd");

    // lol
    std::cout << std::setw(22) << s1
              << std::setw(22) << s2
              << std::endl;
    std::cout << std::setw(22) << hasher(s1)
              << std::setw(22) << hasher(s2)
              << std::endl;
    std::cout << std::setw(22) << hasher.hash(s1)
              << std::setw(22) << hasher.hash(s2)
              << std::endl;
    std::cout << std::setw(22) << hasher.fingerprint(s1)
              << std::setw(22) << hasher.fingerprint(s2)
              << std::endl;



    //std::cout << file.GetFileName() << std::endl;
    //std::cout << file.GetNextSequence() << std::endl;
    return 0;
}
