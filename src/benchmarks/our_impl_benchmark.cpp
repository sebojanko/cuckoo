//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include <fstream>
#include "../Cuckoo.h"
#include "../SimpleEncoder.h"
#include <ctime>


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


void insertElems(Cuckoo *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Inserting " << elems_list.size() << " elems" << std::endl;

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        c->Insert(*it);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to insert " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
}

void checkExistingElems(Cuckoo *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " inserted elements:" << std::endl;
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (c->Contains(*it)) {
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
    out << "Found percentage - " << float(found)/not_found*100 << "%" << std::endl << std::endl;
}

void checkNonExistingElems(Cuckoo *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " not inserted elements:" << std::endl;
    
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (c->Contains(*it)) {
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
    out << "False positives percentage - " << float(found)/not_found*100. << "%" << std::endl << std::endl;
}

void removeElems(Cuckoo *c, std::vector<uint64_t> elems_list, std::ofstream& out) {
    out << "Removing " << elems_list.size() << " elems" << std::endl;

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        c->Remove(*it);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to remove " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
}

int main(int argc, const char* argv[]) {
    SimpleEncoder encoder{};

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

    Cuckoo c = Cuckoo();
    Cuckoo c2 = Cuckoo(Hash::MD5);
    Cuckoo c3 = Cuckoo(Hash::SHA1);
    Cuckoo c4 = Cuckoo(Hash::TIMS);
    Cuckoo c5 = Cuckoo(Hash::IDENTITY);


    out << "IDENTITY (no hash)" << std::endl;
    insertElems(&c5, input_vector, out);
    checkExistingElems(&c5, input_vector, out);
    checkNonExistingElems(&c5, nonex_vector, out);
    removeElems(&c5, input_vector, out);
    checkExistingElems(&c5, input_vector, out);
    checkNonExistingElems(&c5, nonex_vector, out);
    
    out << std::string(20, '-') << std::endl;
 
    out << "Two independent multiply shift (TIMS)" << std::endl;
    insertElems(&c4, input_vector, out);
    checkExistingElems(&c4, input_vector, out);
    checkNonExistingElems(&c4, nonex_vector, out);
    removeElems(&c4, input_vector, out);
    checkExistingElems(&c4, input_vector, out);
    checkNonExistingElems(&c4, nonex_vector, out);
    
    out << std::string(20, '-') << std::endl;
 
    out << "MD5 hash" << std::endl;
    insertElems(&c2, input_vector, out);
    checkExistingElems(&c2, input_vector, out);
    checkNonExistingElems(&c2, nonex_vector, out);
    removeElems(&c2, input_vector, out);
    checkExistingElems(&c2, input_vector, out);
    checkNonExistingElems(&c2, nonex_vector, out);
    
    out << std::string(20, '-') << std::endl;
    
    out << "std::hash" << std::endl;
    insertElems(&c, input_vector, out);
    checkExistingElems(&c, input_vector, out);
    checkNonExistingElems(&c, nonex_vector, out);
    removeElems(&c, input_vector, out);
    checkExistingElems(&c, input_vector, out);
    checkNonExistingElems(&c, nonex_vector, out);
    
    out << std::string(20, '-') << std::endl;

    out << "SHA1 hash" << std::endl;
    insertElems(&c3, input_vector, out);
    checkExistingElems(&c3, input_vector, out);
    checkNonExistingElems(&c3, nonex_vector, out);
    removeElems(&c3, input_vector, out);
    checkExistingElems(&c3, input_vector, out);
    checkNonExistingElems(&c3, nonex_vector, out);

    return 0;
}
