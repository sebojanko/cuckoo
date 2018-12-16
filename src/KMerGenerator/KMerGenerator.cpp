#include <iostream>
#include <random>
#include "KMerGenerator.h"
#include "../FastADocument.h"



std::string KMerGenerator::GenerateRandomKMer(int length) {
	std::string out = "";
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 3);

    for (int i = 0; i < length; ++i) {
        out += BASES[dist(mt)];
    }

    return out;
}

std::string KMerGenerator::ExtractRandomKMer(std::string filename, int length) {	
	FastADocument fad(filename);
	std::string sequence = fad.GetNextSequence();
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, sequence.length()-length);
	
	return sequence.substr(dist(mt), length);
}