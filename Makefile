CXX=g++
CXXFLAGS=-Wall -std=c++17 -lcrypto -lssl
SOURCES=src/main.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp

all: cuckoo test gen bench

cuckoo: src/main.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp
	$(CXX) $(CXXFLAGS) $^ -o cuckoo

test: src/tests/main.cpp src/Table.cpp src/Bucket.cpp src/Hash.cpp src/FastADocument.cpp src/KMerGenerator/KMerGenerator.cpp
	$(CXX) $(CXXFLAGS) $^ -o test

gen: src/KMerGenerator/main.cpp src/FastADocument.cpp src/KMerGenerator/KMerGenerator.cpp
	$(CXX) $(CXXFLAGS) $^ -o kmergen

bench: src/benchmarks/main.cpp src/Cuckoo.cpp src/Bucket.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp
	$(CXX) $(CXXFLAGS) -O3 $^ -o benchmark

clean:
	@rm -f *.o cuckoo test benchmark kmergen
