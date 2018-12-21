//
// Created by sebo on 11/28/18.
//

#include <iostream>
#include "Cuckoo.h"

Cuckoo::Cuckoo() {
	Hasher hasher(8);
	table_ = Table(&hasher);
}

// Ovdje hasheri razlicitih cuckoo objekata imaju iste reference
// i iz nekog razloga svi hasheri imaju argument Hash::STL
// (defaultni stl hash). Zato u benchmarku svi imaju iste rezultate.
// Ako se ove linije zamjene sa zakomentiranima, onda izgleda da
// dobro radi.
Cuckoo::Cuckoo(Hash h) {
    Hasher *hasher = new Hasher(8, h);
    std::cout << static_cast<std::underlying_type<Hash>::type>(h) << std::endl;
    std::cout << "Hasher ref: " << &hasher 
              << "  Cuckoo this: " << this << std::endl;
    table_ = Table(hasher);

}

void Cuckoo::Insert(std::string element) {
	table_.Insert(element);
}

void Cuckoo::Insert(int element) {
	table_.Insert(element);
}

bool Cuckoo::Remove(std::string element) {
	return table_.Remove(element);
}

bool Cuckoo::Contains(std::string element) {
	return table_.Contains(element);
}

bool Cuckoo::Contains(int element) {
	return table_.Contains(element);
}

void Cuckoo::Print() {
	table_.Print();
}
