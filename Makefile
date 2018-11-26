all:
	g++ -std=c++17 src/main.cpp src/Bucket.cpp src/FastADocument.cpp src/GeneSequence.cpp src/hash.cpp src/table.cpp -o cuckoo
test:
	g++ -std=c++17 src/tests/TableTests.cpp src/table.cpp -o test