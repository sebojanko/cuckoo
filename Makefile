all:
	g++ -std=c++17 src/main.cpp src/Bucket.cpp src/FastADocument.cpp src/GeneSequence.cpp src/hash.cpp src/table.cpp -o cuckoo
test:
	g++ -std=c++17 src/tests/main.cpp src/table.cpp src/Bucket.cpp -o test