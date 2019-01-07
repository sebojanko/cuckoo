#include <iostream>
#include <assert.h>
#include "../KMerGenerator/KMerGenerator.h"


void test_KMerGenerator__GenerateRandom10Mer__ReturnsStringOfLength10() {
    KMerGenerator kmg = KMerGenerator();
    auto kmer = kmg.GenerateRandomKMer(10);
    assert(kmer.length() == 10);
    std::cout << "PASS test_KMerGenerator__GenerateRandom10Mer__ReturnsStringOfLength10" << std::endl;
}

void test_KMerGenerator__GenerateRandom1Mer__ReturnsStringOfLength1() {
    KMerGenerator kmg = KMerGenerator();
    auto kmer = kmg.GenerateRandomKMer(1);
    assert(kmer.length() == 1);
    std::cout << "PASS test_KMerGenerator__GenerateRandom1Mer__ReturnsStringOfLength1" << std::endl;
}

void test_KMerGenerator__GenerateRandom100Mer__ReturnsStringOfLength100() {
    KMerGenerator kmg = KMerGenerator();
    auto kmer = kmg.GenerateRandomKMer(100);
    assert(kmer.length() == 100);
    std::cout << "PASS test_KMerGenerator__GenerateRandom100Mer__ReturnsStringOfLength100" << std::endl;
}

void test_KMerGenerator__GenerateRandom500Mer__ReturnsStringOfLength500() {
    KMerGenerator kmg = KMerGenerator();
    auto kmer = kmg.GenerateRandomKMer(500);
    assert(kmer.length() == 500);
    std::cout << "PASS test_KMerGenerator__GenerateRandom500Mer__ReturnsStringOfLength500" << std::endl;
}

void test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength10(std::string filename) {
	KMerGenerator kmg = KMerGenerator(filename);
    auto kmer = kmg.ExtractRandomKMer(10);
    assert(kmer.length() == 10);
    std::cout << "PASS test_KMerGenerator__ExtractRandomKMer_ReturnsStringOfLength10" << std::endl;
}

void test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength1(std::string filename) {
	KMerGenerator kmg = KMerGenerator(filename);
    auto kmer = kmg.ExtractRandomKMer(1);
    assert(kmer.length() == 1);
    std::cout << "PASS test_KMerGenerator__ExtractRandomKMer_ReturnsStringOfLength1" << std::endl;
}

void test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength100(std::string filename) {
	KMerGenerator kmg = KMerGenerator(filename);
    auto kmer = kmg.ExtractRandomKMer(100);
    assert(kmer.length() == 100);
    std::cout << "PASS test_KMerGenerator__ExtractRandomKMer_ReturnsStringOfLength100" << std::endl;
}

void test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength500(std::string filename) {
	KMerGenerator kmg = KMerGenerator(filename);
    auto kmer = kmg.ExtractRandomKMer(500);
    assert(kmer.length() == 500);
    std::cout << "PASS test_KMerGenerator__ExtractRandomKMer_ReturnsStringOfLength500" << std::endl;
}
