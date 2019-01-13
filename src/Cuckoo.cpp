//
// Created by sebo on 11/28/18.
//

#include "Cuckoo.h"

Cuckoo::Cuckoo() {
	Hasher hasher(8);
	table_ = CompactTable(&hasher);
}

// Ovdje hasheri razlicitih cuckoo objekata imaju iste reference
// i iz nekog razloga svi hasheri imaju argument Hash::STL
// (defaultni stl hash). Zato u benchmarku svi imaju iste rezultate.
// Ako se ove linije zamjene sa zakomentiranima, onda izgleda da
// dobro radi.
Cuckoo::Cuckoo(HashType h, int fprint_size, int bucket_size, int max_num_elements) {
    size_t bucket_count = pow(2, ceil(log2(std::max<uint64_t>(1, max_num_elements / bucket_size))));
    double load_factor = (double)max_num_elements / bucket_count / bucket_size;
    if (load_factor > 0.96) {
        bucket_count *= 2;
    }
    std::cout << "Load factor: " << load_factor << std::endl;
    std::cout << "Bucket count: " << bucket_count << std::endl;
    Hasher *hasher = new Hasher(fprint_size, h);
    table_ = CompactTable(hasher, bucket_size, bucket_count);
}

template<class T>
bool Cuckoo::Insert(const T& element) {
	return table_.Insert(element);
}

template<class T>
bool Cuckoo::Remove(const T& element) {
	return table_.Remove(element);
}

template<class T>
bool Cuckoo::Contains(const T& element) const {
	return table_.Contains(element);
}

void Cuckoo::Print() {
	table_.Print();
}
