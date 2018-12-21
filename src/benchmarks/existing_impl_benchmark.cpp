//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>
#include "../src/cuckoofilter.h"
#include "../src/hashutil.h"
#include "SimpleEncoder.h"


#define NO_OF_ELEMS_TO_INSERT 1'000'000
#define NO_OF_EXISTING_ELEMS_TO_CHECK 500'000
#define NO_OF_NON_EXISTING_ELEMS_TO_CHECK 500'000

using namespace cuckoofilter;


std::string getKMerDataInputArg(int argc, const char* argv[]) {
  if (argc < 2) {
        std::cout << "Missing input KMer file argument." << std::endl;
        exit(-1);
    }
  return argv[1];
}

std::string getKMerDataNonExistingArg(int argc, const char* argv[]) {
  if (argc < 3) {
        std::cout << "Missing non-existing KMer file argument." << std::endl;
        exit(-1);
    }
  return argv[2];
}

void insertElems(CuckooFilter<int, 16> *c, int no_of_elems, std::vector<int> elems_list) {
    std::cout << "Inserting " << no_of_elems << " elems" << std::endl;

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        c->Add(*it);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "Time to insert " << no_of_elems << " elems: " << elapsed_secs << std::endl << std::endl;
}

void checkExistingElems(CuckooFilter<int, 16> *c, int no_of_elems, std::vector<int> elems_list) {
    std::cout << "Checking " << no_of_elems << " inserted elements:" << std::endl;
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        std::cout << *it << std::endl;
        if (c->Contain(*it)) {
            found++;
        } else {
            not_found++;
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "Time to check existing " << no_of_elems << " elems: " << elapsed_secs << std::endl;
    std::cout << "Found - " << found << std::endl;
    std::cout << "Not found - " << not_found << std::endl;
    std::cout << "Found percentage - " << float(not_found)/found*100 << "%" << std::endl << std::endl;
}

void checkNonExistingElems(CuckooFilter<int, 16> *c, int no_of_elems, std::vector<int> elems_list) {
    std::cout << "Checking " << no_of_elems << " not inserted elements:" << std::endl;
    
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (c->Contain(*it)) {
            found++;
        } else {
            not_found++;
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "Time to check non existing " << no_of_elems << " elems: " << elapsed_secs << std::endl;
    std::cout << "Found - " << found << std::endl;
    std::cout << "Not found - " << not_found << std::endl;
    std::cout << "False positives percentage - " << float(found)/not_found*100. << "%" << std::endl;
}

int main(int argc, const char* argv[]) {
    // TODO ubacit formatiranje ispisa
    int total_items{1'000'000};
    
    SimpleEncoder encoder{3};
    std::vector<int> input_vector{};
    std::vector<int> nonex_vector{};
    std::string kMerInputFilename{getKMerDataInputArg(argc, argv)};
    std::string kMerNonExFilename{getKMerDataNonExistingArg(argc, argv)};
    std::ifstream infile(kMerInputFilename);
    std::ifstream nonex_file(kMerNonExFilename);
    std::string line;

    while (std::getline(infile, line)) {
        input_vector.push_back(encoder.encode(line));
    }

    while (std::getline(nonex_file, line)) {
        nonex_vector.push_back(encoder.encode(line));
    }

    CuckooFilter<int, 16> c(total_items);
    /*Cuckoo c2 = Cuckoo(Hash::MD5);
    Cuckoo c3 = Cuckoo(Hash::SHA1);
    Cuckoo c4 = Cuckoo(Hash::TIMS);
    Cuckoo c5 = Cuckoo(Hash::IDENTITY);*/


    /*std::cout << "IDENTITY (no hash)" << std::endl;
    insertElems(&c5, NO_OF_ELEMS_TO_INSERT, input_vector);
    checkExistingElems(&c5, NO_OF_EXISTING_ELEMS_TO_CHECK, input_vector);
    checkNonExistingElems(&c5, NO_OF_NON_EXISTING_ELEMS_TO_CHECK, nonex_vector);
    
    std::cout << std::string(20, '-') << std::endl;
 
    std::cout << "Two independent multiply shift (TIMS)" << std::endl;
    insertElems(&c4, NO_OF_ELEMS_TO_INSERT, input_vector);
    checkExistingElems(&c4, NO_OF_EXISTING_ELEMS_TO_CHECK, input_vector);
    checkNonExistingElems(&c4, NO_OF_NON_EXISTING_ELEMS_TO_CHECK, nonex_vector);
    
    std::cout << std::string(20, '-') << std::endl;
 
    std::cout << "MD5 hash" << std::endl;
    insertElems(&c2, NO_OF_ELEMS_TO_INSERT, input_vector);
    checkExistingElems(&c2, NO_OF_EXISTING_ELEMS_TO_CHECK, input_vector);
    checkNonExistingElems(&c2, NO_OF_NON_EXISTING_ELEMS_TO_CHECK, nonex_vector);
    
    std::cout << std::string(20, '-') << std::endl;

    std::cout << "SHA1 hash" << std::endl;
    insertElems(&c3, NO_OF_ELEMS_TO_INSERT, input_vector);
    checkExistingElems(&c3, NO_OF_EXISTING_ELEMS_TO_CHECK, input_vector);
    checkNonExistingElems(&c3, NO_OF_NON_EXISTING_ELEMS_TO_CHECK, nonex_vector);
    */

    std::cout << std::string(20, '-') << std::endl;
    
    std::cout << "std::hash" << std::endl;
    insertElems(&c, NO_OF_ELEMS_TO_INSERT, input_vector);
    checkExistingElems(&c, NO_OF_EXISTING_ELEMS_TO_CHECK, input_vector);
    checkNonExistingElems(&c, NO_OF_NON_EXISTING_ELEMS_TO_CHECK, nonex_vector);
    

    return 0;
}
