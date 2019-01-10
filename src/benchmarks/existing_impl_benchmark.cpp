//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <set>
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
    SimpleEncoder encoder{};

    std::set<std::string> input_str_set{};
    std::set<uint64_t> input_enc_set{};
    std::vector<uint64_t> input_vector;

    std::set<std::string> nonex_str_set{};
    std::set<uint64_t> nonex_enc_set{};
    std::vector<uint64_t> nonex_vector{};

    std::string kMerInputFilename{getKMerDataInputArg(argc, argv)};
    std::string kMerNonExFilename{getKMerDataNonExistingArg(argc, argv)};
    std::string outputFilename{getOutputArg(argc, argv)};

    std::ifstream infile(kMerInputFilename);
    std::ifstream nonex_file(kMerNonExFilename);
    std::ofstream out(outputFilename);

    std::string line;

while (std::getline(infile, line)) {
        input_str_set.insert(line);
        input_enc_set.insert(encoder.encode(line));
    }

    out << "Number of unique k-mers for input - " << input_str_set.size() << std::endl;
    out << "Number of unique encodings for input - " << input_enc_set.size() << std::endl;
    std::copy(input_enc_set.begin(), input_enc_set.end(), std::back_inserter(input_vector));


    while (std::getline(nonex_file, line)) {
        nonex_str_set.insert(line);
        nonex_enc_set.insert(encoder.encode(line));
    }
    std::copy(nonex_enc_set.begin(), nonex_enc_set.end(), std::back_inserter(nonex_vector));

    out << "Number of unique nonexistent k-mers - " << nonex_str_set.size() << std::endl;
    out << "Number of unique nonexistent encodings - " << nonex_enc_set.size() << std::endl;


    std::vector<std::string> intersection;
 
    std::set_intersection(input_str_set.begin(), input_str_set.end(),
                          nonex_str_set.begin(), nonex_str_set.end(),
                          std::back_inserter(intersection));
    out << "Intersection from input file - " << intersection.size() << std::endl << std::endl;
 
    std::vector<uint64_t> difference_encoding;
    std::set_difference(nonex_enc_set.begin(), nonex_enc_set.end(),
                          input_enc_set.begin(), input_enc_set.end(),
                          std::back_inserter(difference_encoding));
    out << "Intersecting encodings from input file - " << abs((int) difference_encoding.size() - (int) input_enc_set.size())<< std::endl << std::endl;


    nonex_vector.clear();
    std::copy(difference_encoding.begin(), difference_encoding.end(), std::back_inserter(nonex_vector));

    CuckooFilter<uint64_t, 8>                                               c1(input_vector.size());
    CuckooFilter<uint64_t, 16>                                              c2(input_vector.size());
    CuckooFilter<uint64_t, 8,  PackedTable>                                 c3(input_vector.size());
    CuckooFilter<uint64_t, 16, PackedTable>                                 c4(input_vector.size());
    CuckooFilter<uint64_t, 8,  SingleTable, TwoIndependentMultiplyShift>    c5(input_vector.size());
    CuckooFilter<uint64_t, 16, SingleTable, TwoIndependentMultiplyShift>    c6(input_vector.size());
    CuckooFilter<uint64_t, 8,  SingleTable, SimpleTabulation>               c7(input_vector.size());
    CuckooFilter<uint64_t, 16, SingleTable, SimpleTabulation>               c8(input_vector.size());
    CuckooFilter<uint64_t, 8,  PackedTable, TwoIndependentMultiplyShift>    c9(input_vector.size());
    CuckooFilter<uint64_t, 16, PackedTable, TwoIndependentMultiplyShift>    c10(input_vector.size());
    CuckooFilter<uint64_t, 8,  PackedTable, SimpleTabulation>               c11(input_vector.size());
    CuckooFilter<uint64_t, 16, PackedTable, SimpleTabulation>               c12(input_vector.size());

  
    out << "8bit, SingleTable, Default" << std::endl;
    insertElems(&c1, input_vector, out);
    checkExistingElems(&c1, input_vector, out);
    checkNonExistingElems(&c1, nonex_vector, out);
    removeElems(&c1, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    out << "16bit, SingleTable, Default" << std::endl;
    insertElems(&c2, input_vector, out);
    checkExistingElems(&c2, input_vector, out);
    checkNonExistingElems(&c2, nonex_vector, out);
    removeElems(&c2, input_vector, out);

    out << std::string(20, '-') << std::endl;
        
    out << "8bit, PackedTable, Default" << std::endl;
    insertElems(&c3, input_vector, out);
    checkExistingElems(&c3, input_vector, out);
    checkNonExistingElems(&c3, nonex_vector, out);
    removeElems(&c3, input_vector, out);

    out << std::string(20, '-') << std::endl;
        
    out << "16bit, PackedTable, Default" << std::endl;
    insertElems(&c4, input_vector, out);
    checkExistingElems(&c4, input_vector, out);
    checkNonExistingElems(&c4, nonex_vector, out);
    removeElems(&c4, input_vector, out);

    out << std::string(20, '-') << std::endl;
        
    out << "8bit, SingleTable, TwoIndependentMultiplyShift" << std::endl;
    insertElems(&c5, input_vector, out);
    checkExistingElems(&c5, input_vector, out);
    checkNonExistingElems(&c5, nonex_vector, out);
    removeElems(&c5, input_vector, out);

    out << std::string(20, '-') << std::endl;

    out << "16bit, SingleTable, TwoIndependentMultiplyShift" << std::endl;
    insertElems(&c6, input_vector, out);
    checkExistingElems(&c6, input_vector, out);
    checkNonExistingElems(&c6, nonex_vector, out);
    removeElems(&c6, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    out << "8bit, SingleTable, SimpleTabulation" << std::endl;
    insertElems(&c7, input_vector, out);
    checkExistingElems(&c7, input_vector, out);
    checkNonExistingElems(&c7, nonex_vector, out);
    removeElems(&c7, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    out << "16bit, SingleTable, SimpleTabulation" << std::endl;
    insertElems(&c8, input_vector, out);
    checkExistingElems(&c8, input_vector, out);
    checkNonExistingElems(&c8, nonex_vector, out);
    removeElems(&c8, input_vector, out);
    
    out << std::string(20, '-') << std::endl;
    
    out << "8bit, PackedTable, TwoIndependentMultiplyShift" << std::endl;
    insertElems(&c9, input_vector, out);
    checkExistingElems(&c9, input_vector, out);
    checkNonExistingElems(&c9, nonex_vector, out);
    removeElems(&c9, input_vector, out);
    
    out << std::string(20, '-') << std::endl;
    
    out << "16bit, PackedTable, TwoIndependentMultiplyShift" << std::endl;
    insertElems(&c10, input_vector, out);
    checkExistingElems(&c10, input_vector, out);
    checkNonExistingElems(&c10, nonex_vector, out);
    removeElems(&c10, input_vector, out);
    
    out << std::string(20, '-') << std::endl;
    
    out << "8bit, PackedTable, SimpleTabulation" << std::endl;
    insertElems(&c11, input_vector, out);
    checkExistingElems(&c11, input_vector, out);
    checkNonExistingElems(&c11, nonex_vector, out);
    removeElems(&c11, input_vector, out);
    
    out << std::string(20, '-') << std::endl;
    
    out << "16, PackedTable, SimpleTabulation" << std::endl;
    insertElems(&c12, input_vector, out);
    checkExistingElems(&c12, input_vector, out);
    checkNonExistingElems(&c12, nonex_vector, out);
    removeElems(&c12, input_vector, out);

    out << std::string(20, '-') << std::endl;
    
    

    return 0;
}
