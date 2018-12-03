//
// Created by sebo on 12/3/18.
//

#ifndef CUCKOO_KMERGENERATOR_H
#define CUCKOO_KMERGENERATOR_H

#include <array>
#include <map>

class KMerGenerator {
private:
    const char BASES[4] = {'A', 'G', 'C', 'T'};

public:
    std::string GenerateRandomKMer(int length);
    std::string ExtractRandomKMer(int length);


};

#endif //CUCKOO_KMERGENERATOR_H
