//
// Created by sebo on 12/3/18.
//

#ifndef CUCKOO_KMERGENERATOR_H
#define CUCKOO_KMERGENERATOR_H

#include <array>
#include <map>

#include "../FastADocument.h"

class KMerGenerator {
private:
    const char BASES[4] = {'A', 'G', 'C', 'T'};
    std::string sequence;

public:
    std::string GenerateRandomKMer(int length);
    std::string ExtractRandomKMer(std::string filename, int length);

    KMerGenerator() = default;
    KMerGenerator(std::string filename) {
        FastADocument document = FastADocument(filename);
        sequence = document.GetNextSequence();
    }


};

#endif //CUCKOO_KMERGENERATOR_H
