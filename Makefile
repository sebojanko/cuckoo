all:
	g++ -std=c++17 src/main.cpp src/Bucket.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp src/KMerGenerator.cpp -o cuckoo
test:
	g++ -std=c++17 src/tests/main.cpp src/Table.cpp src/Bucket.cpp src/Hash.cpp src/FastADocument.cpp src/KMerGenerator.cpp -o test
gen:
	g++ -std=c++17 src/KMerGenerator/main.cpp src/FastADocument.cpp src/KMerGenerator/KMerGenerator.cpp	 -o kmergen