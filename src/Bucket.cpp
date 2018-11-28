#include "Bucket.h"

Bucket::Bucket() {
}


Bucket::Bucket(std::string value) {
    entries_[0] = value;
    ++size_;
}

Bucket::~Bucket() {

}

bool Bucket::Push(std::string value) {
    if (size_ == 10) {
        std::cout << "Bucket full!";
        return false;
    }

    for (int i=0; i < 10; ++i) {
        if (!entries_[i].compare("")) {
            entries_[i] = value;
            ++size_;
            return true;
        }
    }
    return false;
}

bool Bucket::Contains(std::string s) {
    for (int i = 0; i < 10; ++i) {
        if (!entries_[i].compare(s)) {
            return true;
        }
    }
    return false;
}

bool Bucket::Remove(std::string s) {
    for (int i = 0; i < 10; ++i) {
        if (!entries_[i].compare(s)) {
            entries_[i] = "";
            --size_;
            return true;
        }
    }
    return false;
}

std::string Bucket::Get(int index) {
    if (index < 0 || index > size_) {
        return "";
    }
    return entries_[index];
}

//for debugging purposes
void Bucket::print() {
    for (auto v : entries_) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}
