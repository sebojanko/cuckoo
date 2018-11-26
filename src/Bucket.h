#ifndef BUCKET_H
#define BUCKET_H

#include <string>
#include <iostream>

class Bucket {
    public:
        struct Entry {
            std::string value;
            struct Entry* next;
        };

        Bucket();
        Bucket(std::string);
        ~Bucket();
        Bucket* Push(std::string);
        Entry* Get(int);
        int GetSize() { return size_; };
        void print();

    private:
        int size_ = 0;
        Entry* entries_;

};
#endif
