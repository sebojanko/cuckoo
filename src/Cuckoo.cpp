//
// Created by sebo on 11/28/18.
//

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
    table_ = Table(hasher);
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
