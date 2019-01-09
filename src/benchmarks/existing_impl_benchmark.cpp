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

std::string getOutputArg(int argc, const char* argv[]) {
  if (argc < 4) {
        std::cout << "Missing output file argument." << std::endl;
        exit(-1);
    }
  return argv[3];
}

template <class T>
void insertElems(T *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Inserting " << elems_list.size() << " elems" << std::endl;

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        c->Add(*it);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to insert " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
}

template <class T>
void checkExistingElems(T *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " inserted elements:" << std::endl;
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
    
    out << "Time to check existing " << elems_list.size() << " elems: " << elapsed_secs << std::endl;
    out << "Found - " << found << std::endl;
    out << "Not found - " << not_found << std::endl;
    out << "Found percentage - " << float(found)/elems_list.size()*100 << "%" << std::endl << std::endl;
}

template <class T>
void checkNonExistingElems(T *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " not inserted elements:" << std::endl;
    
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
    
    out << "Time to check non existing " << elems_list.size() << " elems: " << elapsed_secs << std::endl;
    out << "Found - " << found << std::endl;
    out << "Not found - " << not_found << std::endl;
    out << "False positives percentage - " << float(found)/elems_list.size()*100. << "%" << std::endl << std::endl;
}

template <class T>
void removeElems(T *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Removing " << elems_list.size() << " elems" << std::endl;

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        c->Delete(*it);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to remove " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
}

int main(int argc, const char* argv[]) {    
    SimpleEncoder encoder{3};
    std::vector<uint64_t> input_vector{};
    std::vector<uint64_t> nonex_vector{};
    std::string kMerInputFilename{getKMerDataInputArg(argc, argv)};
    std::string kMerNonExFilename{getKMerDataNonExistingArg(argc, argv)};
    std::string outputFilename{getOutputArg(argc, argv)};
    std::ifstream infile(kMerInputFilename);
    std::ifstream nonex_file(kMerNonExFilename);
    std::ofstream out(outputFilename);
    std::string line;

    while (std::getline(infile, line)) {
        input_vector.push_back(encoder.encode(line));
    }

    while (std::getline(nonex_file, line)) {
        nonex_vector.push_back(encoder.encode(line));
    }

    CuckooFilter<uint64_t, 17> c(input_vector.size());
    CuckooFilter<uint64_t, 17, SingleTable, TwoIndependentMultiplyShift> c2(input_vector.size());
    CuckooFilter<uint64_t, 17, SingleTable, SimpleTabulation> c3(input_vector.size());

  
    out << "std::hash" << std::endl;
    insertElems(&c, input_vector, out);
    checkExistingElems(&c, input_vector, out);
    checkNonExistingElems(&c, nonex_vector, out);
    removeElems(&c, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    out << "TIMS" << std::endl;
    insertElems(&c2, input_vector, out);
    checkExistingElems(&c2, input_vector, out);
    checkNonExistingElems(&c2, nonex_vector, out);
    removeElems(&c2, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    out << "SimpleTabulation" << std::endl;
    insertElems(&c3, input_vector, out);
    checkExistingElems(&c3, input_vector, out);
    checkNonExistingElems(&c3, nonex_vector, out);
    removeElems(&c3, input_vector, out);
    

    return 0;
}
