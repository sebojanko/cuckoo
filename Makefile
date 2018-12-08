all:
	g++ -std=c++17 src/main.cpp src/Bucket.cpp src/Cuckoo.cpp src/FastADocument.cpp src/GeneSequence.cpp src/Hash.cpp src/Table.cpp -o cuckoo -lcrypto -lssl
test:
	g++ -std=c++17 src/tests/main.cpp src/Table.cpp src/Bucket.cpp src/Hash.cpp -o test -lcrypto -lssl
