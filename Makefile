CXX=g++
CXXFLAGS=-Wall -std=c++17 -lcrypto -lssl
SOURCES=src/main.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp

all: test gen bench

#cuckoo: src/main.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp
#cuckoo: src/main.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp
#	$(CXX) $^ -o cuckoo $(CXXFLAGS)

test: src/tests/main.cpp src/FastADocument.cpp src/KMerGenerator/KMerGenerator.cpp src/SimpleEncoder.cpp
	$(CXX) $^ -o test $(CXXFLAGS)

gen: src/KMerGenerator/main.cpp src/FastADocument.cpp src/KMerGenerator/KMerGenerator.cpp
	$(CXX) -O3 $^ -o kmergen $(CXXFLAGS)

bench: src/benchmarks/our_impl_benchmark.cpp src/FastADocument.cpp src/GeneSequence.cpp src/SimpleEncoder.cpp
	$(CXX) -O3 $^ -o benchmark $(CXXFLAGS)

clean:
	@rm -f *.o cuckoo test benchmark kmergen
