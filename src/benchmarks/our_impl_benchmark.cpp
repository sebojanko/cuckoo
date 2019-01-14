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

template<class T>
void insertElems(Cuckoo& c, T& elems_list, std::ofstream& out) {
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

template<class T>
void checkExistingElems(Cuckoo& c, T& elems_list, std::ofstream& out) {
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

template<class T>
void checkNonExistingElems(Cuckoo &c, T& elems_list, std::ofstream& out) {
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

template<class T>
void removeElems(Cuckoo& c, T& elems_list, std::ofstream& out) {
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
    std::vector<std::string> input_vector_str{};
    std::set<uint64_t> input_enc_set{};
    std::vector<uint64_t> input_vector_enc{};

    std::set<std::string> nonex_str_set{};
    std::vector<std::string> nonex_vector_str{};
    std::set<uint64_t> nonex_enc_set{};
    std::vector<uint64_t> nonex_vector_enc{};

    std::string kMerInputFilename{getKMerDataInputArg(argc, argv)};
    std::string kMerNonExFilename{getKMerDataNonExistingArg(argc, argv)};
    std::string outputFilename{getOutputArg(argc, argv)};

    std::ifstream infile(kMerInputFilename);
    std::ifstream nonex_file(kMerNonExFilename);
    std::ofstream out(outputFilename);

    std::string line;
    int size{};

    std::getline(infile, line);
    input_str_set.insert(line);
    size = line.length();
    out << "Inserting " << size << "-mers" << std::endl;

    while (std::getline(infile, line)) {
        input_str_set.insert(line);
    }

    if (size <= 20) {
        for (auto l : input_str_set)
            input_enc_set.insert(encoder.Encode(l));
    }

    out << "Number of unique k-mers for input - " << input_str_set.size() << std::endl;
    if (size <= 20) {
        out << "Number of unique encodings for input - " << input_enc_set.size() << std::endl;
        std::copy(input_enc_set.begin(), input_enc_set.end(), std::back_inserter(input_vector_enc));
    } else {
        std::copy(input_str_set.begin(), input_str_set.end(), std::back_inserter(input_vector_str));
    }

    std::getline(nonex_file, line);
    nonex_str_set.insert(line);
    size = line.length();

    while (std::getline(nonex_file, line)) {
        nonex_str_set.insert(line);
    }

     if (size <= 20) {
        for (auto l : nonex_str_set)
            nonex_enc_set.insert(encoder.Encode(l));
    }

    out << "Number of unique nonexistent k-mers - " << nonex_str_set.size() << std::endl;
    if (size <= 20) {
        out << "Number of unique nonexistent encodings - " << nonex_enc_set.size() << std::endl;
        std::copy(nonex_enc_set.begin(), nonex_enc_set.end(), std::back_inserter(nonex_vector_enc));
    } else {
        std::copy(nonex_str_set.begin(), nonex_str_set.end(), std::back_inserter(nonex_vector_str));
    }

    std::vector<std::string> intersection;
 
    std::set_intersection(input_str_set.begin(), input_str_set.end(),
                          nonex_str_set.begin(), nonex_str_set.end(),
                          std::back_inserter(intersection));
    out << "Intersection from input file - " << intersection.size() << std::endl << std::endl;
    

    if (size <= 20) {
        std::vector<uint64_t> difference_encoding_enc;
        std::set_difference(nonex_enc_set.begin(), nonex_enc_set.end(),
                            input_enc_set.begin(), input_enc_set.end(),
                            std::back_inserter(difference_encoding_enc));
        nonex_vector_enc.clear();
        std::copy(difference_encoding_enc.begin(), difference_encoding_enc.end(), std::back_inserter(nonex_vector_enc));
        out << "Deleted intersecting encodings from input file - " << nonex_enc_set.size() - difference_encoding_enc.size() << std::endl << std::endl;
    } else {
        std::vector<std::string> difference_encoding_str;
        std::set_difference(nonex_str_set.begin(), nonex_str_set.end(),
                            input_str_set.begin(), input_str_set.end(),
                            std::back_inserter(difference_encoding_str));
        nonex_vector_str.clear();
        std::copy(difference_encoding_str.begin(), difference_encoding_str.end(), std::back_inserter(nonex_vector_str));
        out << "Deleted intersecting strings from input file - " << nonex_str_set.size() - difference_encoding_str.size() << std::endl << std::endl;
    }

    std::vector<Cuckoo> cs;
    if (size <= 20) {
        cs.push_back( Cuckoo(HashType::TIMS, 8, 4, input_vector_enc.size()) );
        cs.push_back( Cuckoo(HashType::MD5, 8, 4, input_vector_enc.size()) );
        cs.push_back( Cuckoo(HashType::SHA1, 8, 4, input_vector_enc.size()) );
    } else {
        cs.push_back( Cuckoo(HashType::TIMS, 8, 4, input_vector_str.size()) );
        cs.push_back( Cuckoo(HashType::MD5, 8, 4, input_vector_str.size()) );
        cs.push_back( Cuckoo(HashType::SHA1, 8, 4, input_vector_str.size()) );
    }
    std::vector<std::string> descriptions = {"Two independent multiply shift (TIMS)", "MD5 hash", "SHA1 hash" };

    auto it = descriptions.begin();

    for(Cuckoo& c : cs) {
        out << std::string(20, '-') << std::endl;
        out << *it++ << std::endl;

        if (size <= 20) {
            insertElems(c, input_vector_enc, out);
            checkExistingElems(c, input_vector_enc, out);
            checkNonExistingElems(c, nonex_vector_enc, out);
            removeElems(c, input_vector_enc, out);
            //checkExistingElems(c, input_vector_enc, out);
            //checkNonExistingElems(c, nonex_vector_enc, out);
        } else {
            insertElems(c, input_vector_str, out);
            checkExistingElems(c, input_vector_str, out);
            checkNonExistingElems(c, nonex_vector_str, out);
            removeElems(c, input_vector_str, out);
            //checkExistingElems(c, input_vector_str, out);
            //checkNonExistingElems(c, nonex_vector_str, out);
        }
    }


    return 0;
}
