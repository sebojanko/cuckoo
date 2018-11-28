//
// Created by sebo on 11/28/18.
//

#include <iostream>
#include "Cuckoo.h"

Cuckoo::Cuckoo() {
	Hasher hasher(8);
	table_ = Table(&hasher);
}

void Cuckoo::Insert(std::string element) {
	table_.Insert(element);
}

bool Cuckoo::Remove(std::string element) {
	return table_.Remove(element);
}

bool Cuckoo::Contains(std::string element) {
	return table_.Contains(element);
}

void Cuckoo::Print() {
	table_.Print();
}
