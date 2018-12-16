//
// Created by sebo on 10/22/18.
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

    clock_t begin = clock();

    for (int i = 0; i < 1000000; i++) {
        c.Insert(i);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time to insert 1M elems (our impl):" << elapsed_secs << std::endl;

    return 0;
}