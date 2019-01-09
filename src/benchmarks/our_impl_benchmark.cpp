//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include <fstream>
#include <ctime>
#include <set>

#include "../Cuckoo.cpp"
#include "../Cuckoo.h"
#include "../SimpleEncoder.h"

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

void insertElems(Cuckoo& c, std::vector<uint64_t>& elems_list, std::ofstream& out) {
    out << "Inserting " << elems_list.size() << " elems" << std::endl;

    int not_inserted = 0;
    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (!c.Insert(*it)) {
            not_inserted++;
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to insert " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
    out << "Failed to insert " << not_inserted << " elements." << std::endl;
}

void checkExistingElems(Cuckoo& c, std::vector<uint64_t>& elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " inserted elements:" << std::endl;
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (c.Contains(*it)) {
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

void checkNonExistingElems(Cuckoo &c, std::vector<uint64_t>& elems_list, std::ofstream& out) {
    out << "Checking " << elems_list.size() << " not inserted elements:" << std::endl;
    
    int found{};
    int not_found{};

    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if (c.Contains(*it)) {
            //std::cout << "Element at index " << it-elems_list.begin() << " is already inside!\n";
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

void removeElems(Cuckoo& c, std::vector<uint64_t>& elems_list, std::ofstream& out) {
    out << "Removing " << elems_list.size() << " elems" << std::endl;

    int not_removed = 0;
    clock_t begin = clock();
    for (auto it = elems_list.begin(); it != elems_list.end(); it++) {
        if(!c.Remove(*it)) {
            not_removed++;
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    out << "Time to remove " << elems_list.size() << " elems: " << elapsed_secs << std::endl << std::endl;
    out << "Failed to remove " << not_removed << " elements." << std::endl;
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
    std::vector<Cuckoo> cs = { Cuckoo(Hash::IDENTITY), Cuckoo(Hash::TIMS), Cuckoo(Hash::MD5), Cuckoo(), Cuckoo(Hash::SHA1) };
    std::vector<std::string> descriptions = { "IDENTITY (no hash)", "Two independent multiply shift (TIMS)", "MD5 hash", "std::hash", "SHA1 hash" };

    auto it = descriptions.begin();


    for(Cuckoo& c : cs) {
        out << *it++ << std::endl;

        insertElems(c, input_vector, out);
        checkExistingElems(c, input_vector, out);
        checkNonExistingElems(c, nonex_vector, out);
        removeElems(c, input_vector, out);
        checkExistingElems(c, input_vector, out);
        checkNonExistingElems(c, nonex_vector, out);

        out << std::string(20, '-') << std::endl;
    }
    //cs[0].Print();

    return 0;
}
