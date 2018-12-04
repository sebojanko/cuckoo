//
// Created by sebo on 10/22/18.
//
#include <iostream>
#include "Table.h"
#include "Bucket.h"
#include "FastADocument.h"
#include "Hash.h"
#include <ctime>


std::string getFilenameArg(int argc, const char* argv[]) {
  if (argc != 2) {
        std::cout << "Missing input file argument." << std::endl;
        exit(-1);
    }
  return argv[1];
}


int main(int argc, const char* argv[]) {
    std::string filename{getFilenameArg(argc, argv)};

    Hasher hasher(8);
    Table table = Table(&hasher);

    //clock_t begin = clock();

    for (int i = 0; i < 10; i++) {
        table.Insert(std::to_string(i));
    }

    //clock_t end = clock();
    //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    FastADocument file(filename);
    //std::cout << file.GetNextSequence() << std::endl;

    // demo

    std::cout << "The table: \n";
    //table.Print();
    if (table.Contains(std::to_string(1))) {
        std::cout << "I contain 1" << std::endl;
    }
    if (table.Contains("50000")) {
        std::cout << "I contain 50000" << std::endl;
    }

    //std::string s1("abc"), s2("abd");

    // lol
    /*
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

    */


    //std::cout << file.GetFileName() << std::endl;
    //std::cout << file.GetNextSequence() << std::endl;
    return 0;
}