#include "Bucket.h"


Bucket::Bucket() {
    entries_ = (Entry*) malloc(sizeof(Entry));
    entries_->value = "";
    entries_->next  = NULL;
    
}


Bucket::Bucket(std::string value) {
    entries_ = (Entry*) malloc(sizeof(Entry));
    entries_->value = value;
    entries_->next  = NULL;
    ++size_;
}

Bucket::Bucket(int value) {
    entries_ = (Entry*) malloc(sizeof(Entry));
    entries_->value = value;
    entries_->next  = NULL;
    ++size_;
}


Bucket::~Bucket() {
    Entry* prev = entries_;
    Entry* curr = entries_;
    do {
        curr = curr->next;
        delete prev;
        prev = curr;
    } while(curr);
}


Bucket* Bucket::Push(std::string value) {
    Entry* new_entry = (Entry*) malloc(sizeof(Entry));
    new_entry->value = value;
    new_entry->next  = entries_;

    entries_ = new_entry;
    ++size_;
    return this;
}

Bucket::Entry* Bucket::Get(int index) {
    Entry* curr = entries_;
    for (int i=0; curr && i < index; curr=curr->next, i++);
    return curr;
}

//for debugging purposes
void Bucket::print() {
    Entry* curr = entries_;
    while (curr) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}
