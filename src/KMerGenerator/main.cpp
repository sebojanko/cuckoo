//
// Created by sebo on 12/07/18.
//
#include <iostream>
#include <fstream>
#include "KMerGenerator.h"


void writeToFile(std::string data, std::string filename) {
    std::ofstream out(filename);
    out << data;
    out.close();
    return;
}

/*
 * Args:
 *  - length of generated/extracted kmer
 *  - how many kmers to generate/extract
 *  - filename of the output file
 *  - "gen" if we want to generate random kmers, "ext" to extract from file
 *  - filename of file to extract kmers from,
 *      needed only if the previous argument is "ext"
 *
 */

// TODO add check if arg exists

int main(int argc, const char* argv[]) {
    KMerGenerator kmg = KMerGenerator();
    
    auto len = atoi(argv[1]);
    auto noOfKMersToWrite = atoi(argv[2]);
    std::string outFilename = argv[3];
    std::string typeOfGeneration = argv[4];

    std::string output = "";

    if (typeOfGeneration == "gen") {
      for (int i = 0; i < noOfKMersToWrite; i++)
        output += kmg.GenerateRandomKMer(len) + "\n";
    }
    if (typeOfGeneration == "ext") {
      std::string extractionFile = argv[5];
      for (int i = 0; i < noOfKMersToWrite; i++)
        output += kmg.ExtractRandomKMer(extractionFile, len) + "\n";
    }


    writeToFile(output, outFilename);

    return 0;
}
