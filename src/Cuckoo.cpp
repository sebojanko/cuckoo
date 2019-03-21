//
// Created by sebo on 11/28/18.
//

#include "Cuckoo.h"

Cuckoo::Cuckoo(HashType h, int fprint_size, int bucket_size,
               int max_num_elements) {
    // number of buckets needed to store max_num_elements
    double n_buckets = static_cast<double>(max_num_elements) / bucket_size;

    // first integer value larger than n_buckets which is also a power of 2
    size_t bucket_count = pow(2, ceil(log2(std::max<uint64_t>(1, n_buckets))));
    double load_factor = n_buckets / bucket_count;
    if (load_factor > 0.96) {
        bucket_count <<= 1;
    }
    std::cout << "Load factor: " << load_factor << std::endl;
    std::cout << "Bucket count: " << bucket_count << std::endl;
    Hasher hasher = Hasher(fprint_size, h);
    table_ = CompactTable(hasher, bucket_size, bucket_count);
    // table_ = Table(hasher, bucket_size, bucket_count);
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
