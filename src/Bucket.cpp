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

bool Bucket::Push(int value) {
    if (size_ == 10) {
        std::cout << "Bucket full!";
        return false;
    }

    for (int i=0; i < 10; ++i) {
        entries_[i] = std::to_string(value);
        ++size_;
        return true;
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

bool Bucket::Contains(int s) {
    for (int i = 0; i < 10; ++i) {
        if (!entries_[i].empty() && int(entries_[i][0]) != 0) {
            if (atoi(entries_[i].c_str()) == s) {
                return true;
            }
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
    if (index < 0 || index >= size_) {
        return "";
    }
    return entries_[index];
}

std::string Bucket::operator[](int i) const {
    if (i < 0 || i >= size_) {
        return "";
    }
    return entries_[i];
}

//for debugging purposes
void Bucket::print() {
    for (auto v : entries_) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}
