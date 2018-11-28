#ifndef BUCKET_H
#define BUCKET_H

#include <string>
#include <iostream>

class Bucket {
    public:
        Bucket();
        Bucket(std::string);
        ~Bucket();
        bool Push(std::string);
        bool Push(int);
        bool Remove(std::string);
        bool Contains(std::string);
        std::string Get(int);
        int GetSize() { return size_; };
        void print();
        std::string operator[](int i) const;

    private:
        int size_ = 0;
        std::string entries_[10] = {""};

};
#endif
