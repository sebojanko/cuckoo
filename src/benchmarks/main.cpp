//
// Created by sebo on 12/16/18.
//
#include <iostream>
#include "../Cuckoo.h"
#include <ctime>

#define NO_OF_ELEMS_TO_INSERT 1'000'000
#define NO_OF_EXISTING_ELEMS_TO_CHECK 500'000
#define NO_OF_NON_EXISTING_ELEMS_TO_CHECK 500'000



std::string getKMerDataFilenameArg(int argc, const char* argv[]) {
  if (argc < 2) {
        std::cout << "Missing test KMer file argument." << std::endl;
        exit(-1);
    }
  return argv[1];
}

void insertElems(Cuckoo *c, int no_of_elems) {
    std::vector<std::string> elems_list{};

    for (int i = 0; i < NO_OF_ELEMS_TO_INSERT; ++i)
    {
        elems_list.push_back(std::to_string(i));
    }
    std::cout << "Inserting " << no_of_elems << " elems" << std::endl;
    clock_t begin = clock();
    for (int i = 0; i < no_of_elems; i++) {
        c->Insert(elems_list.at(i));
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time to insert " << no_of_elems << " elems: " << elapsed_secs << std::endl << std::endl;
}

void checkExistingElems(Cuckoo *c, int no_of_elems) {
    std::vector<std::string> elems_list{};

    for (int i = 0; i < NO_OF_ELEMS_TO_INSERT; ++i)
    {
        elems_list.push_back(std::to_string(i));
    }
    std::cout << "Checking " << no_of_elems << " inserted elements:" << std::endl;
    int found{};
    int not_found{};
    clock_t begin = clock();
    for (int i = 0; i < no_of_elems; i++) {
        if (c->Contains(elems_list.at(i))) {
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

void checkNonExistingElems(Cuckoo *c, int no_of_elems) {
    std::vector<std::string> elems_list{};
    int start = 1'000'000;

    for (int i = start; i < NO_OF_ELEMS_TO_INSERT+start; ++i)
    {
        elems_list.push_back(std::to_string(i));
    }
    std::cout << "Checking " << no_of_elems << " not inserted elements:" << std::endl;
    int found{};
    int not_found{};
    clock_t begin = clock();
    for (int i = start; i < start + no_of_elems; i++) {
        if (c->Contains(elems_list.at(i-start))) {
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

    //std::string KMerDataFilename{getKMerDataFilenameArg(argc, argv)};

    Cuckoo c = Cuckoo();
    Cuckoo c2 = Cuckoo(Hash::MD5);
    Cuckoo c3 = Cuckoo(Hash::SHA1);
    Cuckoo c4 = Cuckoo(Hash::TIMS);
    Cuckoo c5 = Cuckoo(Hash::IDENTITY);


    std::cout << "IDENTITY (no hash)" << std::endl;
    insertElems(&c5, NO_OF_ELEMS_TO_INSERT);    
    checkExistingElems(&c5, NO_OF_EXISTING_ELEMS_TO_CHECK);
    checkNonExistingElems(&c5, NO_OF_NON_EXISTING_ELEMS_TO_CHECK);
    
    std::cout << std::string(20, '-') << std::endl;
 
    std::cout << "Two independent multiply shift (TIMS)" << std::endl;
    insertElems(&c4, NO_OF_ELEMS_TO_INSERT);    
    checkExistingElems(&c4, NO_OF_EXISTING_ELEMS_TO_CHECK);
    checkNonExistingElems(&c4, NO_OF_NON_EXISTING_ELEMS_TO_CHECK);
    
    std::cout << std::string(20, '-') << std::endl;
 
    std::cout << "MD5 hash" << std::endl;
    insertElems(&c2, NO_OF_ELEMS_TO_INSERT);    
    checkExistingElems(&c2, NO_OF_EXISTING_ELEMS_TO_CHECK);
    checkNonExistingElems(&c2, NO_OF_NON_EXISTING_ELEMS_TO_CHECK);
    
    std::cout << std::string(20, '-') << std::endl;
    
    std::cout << "std::hash" << std::endl;
    insertElems(&c, NO_OF_ELEMS_TO_INSERT);    
    checkExistingElems(&c, NO_OF_EXISTING_ELEMS_TO_CHECK);
    checkNonExistingElems(&c, NO_OF_NON_EXISTING_ELEMS_TO_CHECK);
    
    std::cout << std::string(20, '-') << std::endl;

    std::cout << "SHA1 hash" << std::endl;
    insertElems(&c3, NO_OF_ELEMS_TO_INSERT);    
    checkExistingElems(&c3, NO_OF_EXISTING_ELEMS_TO_CHECK);
    checkNonExistingElems(&c3, NO_OF_NON_EXISTING_ELEMS_TO_CHECK);

    return 0;
}
