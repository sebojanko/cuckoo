//
// Created by David on 12/23/18.
//
#include "CompactTable.h"
#include <assert.h>


CompactTable::CompactTable(Hasher *hasher, int bucket_size, size_t min_bucket_count) {
    this->hasher_ = hasher;
    this->bucket_size_ = bucket_size;
    this->bucket_count_ = pow(2, ceil(log2(min_bucket_count)));
    this->max_num_kicks_ = 500;
    uint64_t len = (bucket_size_ + 1) * bucket_count_ + 7;
    table_ = new uint16_t[len];
    memset(table_, 0, len);
}

template<class T>
bool CompactTable::Insert(const T& element) {
    // get hash of element
    uint64_t h = hasher_->Hash(element);

    // calculate the first index using the first 32 bits
    // of the hash and mod with number of buckets.
    // since bucket_cout_ % 2 == 0, we can use &
    uint64_t i1 = (h >> 32) & (bucket_count_ - 1);

    // get fingerprint of hash
    uint16_t f = hasher_->Fingerprint(h);

    // calculate alternate index
    uint64_t i2 = (i1 ^ hasher_->Hash(f)) & (bucket_count_ - 1);

    // check if the alternate index of i2 is i1
    assert(i1 == ((i2 ^ hasher_->Hash(f)) & (bucket_count_ - 1)));

    // The first element in the bucket is reserved and
    // shows the number of items currently in the bucket
    uint16_t n_items = table_[i1 * bucket_size_];
    if (n_items < bucket_size_ - 1) {
        table_[i1 * bucket_size_ + n_items + 1] = f;
        table_[i1 * bucket_size_]++;
        return true;
    }
    n_items = table_[i2 * bucket_size_];
    if (n_items < bucket_size_ - 1) {
        table_[i2 * bucket_size_ + n_items + 1] = f;
        table_[i2 * bucket_size_]++;
        return true;
    }

    // no free buckets, must relocate existing items

    // randomly pick i1 or i2
    uint64_t i = std::rand() % 2 == 0 ? i1 : i2;
    for (int n = 0; n < max_num_kicks_; n++) {
        // randomly select an entry e from bucket[i] and swap with f
        std::swap(f, table_[i * bucket_size_ + 1 + std::rand() % (bucket_size_ - 1)]);

        // hash and mod bucket_cout_
        i = (i ^ hasher_->Hash(f)) & (bucket_count_ - 1);

        n_items = table_[i * bucket_size_];
        if (n_items < bucket_size_ - 1) {
            table_[i * bucket_size_ + n_items + 1] = f;
            table_[i * bucket_size_]++;
            return true;
        }
    }

    // Table is full
    return false;
}

template<class T>
bool CompactTable::Remove(const T& element) {
    uint64_t h = hasher_->Hash(element);  // same as Insert
    uint64_t i1 = (h >> 32) & (bucket_count_ - 1);
    uint16_t f = hasher_->Fingerprint(h);

    uint16_t n_items = table_[i1 * bucket_size_];
    for (uint64_t i = i1 * bucket_size_ + 1; i <= i1 * bucket_size_ + n_items; i++) {
        // remove element if found
        if (table_[i] == f) {
            if (i == i1 * bucket_size_ + bucket_size_ - 1) {
                // if last element in bucket, set value to 0
                table_[i] = 0;
            } else {
                // if the found element is in the middle of the bucket
                // place the last element of the bucket in its place
                table_[i] = table_[i1 * bucket_size_ + n_items];
                table_[i1 * bucket_size_ + n_items] = 0;
            }
            // decrease item count in bucket
            table_[i1 * bucket_size_]--;
            return true;
        }
    }

    uint64_t i2 = (i1 ^ hasher_->Hash(f)) & (bucket_count_ - 1);
    n_items = table_[i2 * bucket_size_];
    for (uint64_t i = i2 * bucket_size_ + 1; i <= i2 * bucket_size_ + n_items; i++) {
        // remove element if found
        if (table_[i] == f) {
            if (i == i2 * bucket_size_ + n_items) {
                // if last element in bucket, set value to 0
                table_[i] = 0;
            } else {
                // if the found element is in the middle of the bucket
                // place the last element of the bucket in its place
                table_[i] = table_[i2 * bucket_size_ + n_items];
                table_[i2 * bucket_size_ + n_items] = 0;
            }
            // decrease item count in bucket
            table_[i2 * bucket_size_]--;
            return true;
        }
    }

    return false;
}

template<class T>
bool CompactTable::Contains(const T& element) const {
    uint64_t h = hasher_->Hash(element);  // same as Insert
    uint64_t i1 = (h >> 32) & (bucket_count_ - 1);
    uint16_t f = hasher_->Fingerprint(h);

    uint16_t n_items = table_[i1 * bucket_size_];
    for (uint64_t i = i1 * bucket_size_ + 1; i <= i1 * bucket_size_ + n_items; i++) {
        if (table_[i] == f) {
            return true;
        }
    }

    uint64_t i2 = (i1 ^ hasher_->Hash(f)) & (bucket_count_ - 1);
    n_items = table_[i2 * bucket_size_];
    for (uint64_t i = i2 * bucket_size_ + 1; i <= i2 * bucket_size_ + n_items; i++) {
        if (table_[i] == f) {
            return true;
        }
    }

    return false;
}

void CompactTable::Print() {
    for (uint64_t i = 0; i < bucket_count_; i++) {
        if (table_[i * bucket_size_] > 0) {
            std::cout << "Bucket " << std::setw(6) << i << ": ";
            for (size_t j = 0; j < bucket_size_; j++) {
                std::cout << std::setw(6) << table_[i * bucket_size_ + j] << " ";
            }
            std::cout << std::endl;
        }
    }
}
