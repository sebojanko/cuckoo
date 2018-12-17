//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include "../Cuckoo.h"
#include <ctime>



std::string getKMerDataFilenameArg(int argc, const char* argv[]) {
  if (argc < 2) {
        std::cout << "Missing test KMer file argument." << std::endl;
        exit(-1);
    }
  return argv[1];
}


int main(int argc, const char* argv[]) {
    std::string KMerDataFilename{getKMerDataFilenameArg(argc, argv)};

    Cuckoo c = Cuckoo();

    std::cout << "Inserting 1M elems" << std::endl;

    clock_t begin = clock();
    for (int i = 0; i < 1000000; i++) {
        c.Insert(i);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time to insert 1M elems (our impl):" << elapsed_secs << std::endl;
    
    std::cout << "Checking 50000 inserted elements:" << std::endl;
    int found{};
    int not_found{};
    begin = clock();
    for (int i = 0; i < 500000; i++) {
        if (c.Contains(i)) {
            found++;
        } else {
            not_found++;
        }
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time to check existing 500000 elems (our impl):" << elapsed_secs << std::endl;
    std::cout << "Found - " << found << std::endl;
    std::cout << "Not found - " << not_found << std::endl;

    std::cout << "Checking 50000 not inserted elements:" << std::endl;
    found = 0;
    not_found = 0;
    begin = clock();
    for (int i = 1'000'000; i < 1500000; i++) {
        if (c.Contains(i)) {
            found++;
        } else {
            not_found++;
        }
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time to check non existing 500000 elems (our impl):" << elapsed_secs << std::endl;
    std::cout << "Found - " << found << std::endl;
    std::cout << "Not found - " << not_found << std::endl;

    return 0;
}