#include <iostream>
#include <assert.h>
#include "../Table.h"
#include "../Hash.h"

void test_Table__InsertedOneElement__FindsOneElement() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    assert(t.Contains("1"));
    std::cout << "PASS test_Table__InsertedOneElement__FindsOneElement" << std::endl;
}

void test_Table__InsertedOneElement__SearchForAnother() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    assert(!t.Contains("2"));
    std::cout << "PASS test_Table__InsertedOneElement__SearchForAnother" << std::endl;
}

void test_Table__InsertedTwoElements__FindsBoth() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    t.Insert("2");
    assert(t.Contains("1"));
    assert(t.Contains("2"));
    std::cout << "PASS test_Table__InsertedTwoElements__FindsBoth" << std::endl;
}

void test_Table__InsertedOneElement__DeletesOneElement() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    assert(t.Remove("1"));
    assert(!t.Contains("1"));
    std::cout << "PASS test_Table__InsertedOneElement__DeletesOneElement" << std::endl;
}

void test_Table__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    assert(!t.Remove("2"));
    assert(t.Contains("1"));
    std::cout << "PASS test_Table__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement" << std::endl;
}

void test_Table__InsertedTwoElements__DeletesBoth() {
    Hasher hasher(8);
    Table t = Table(&hasher);
    t.Insert("1");
    t.Insert("2");
    assert(t.Remove("1"));
    assert(t.Remove("2"));
    assert(!t.Contains("1"));
    assert(!t.Contains("2"));
    std::cout << "PASS test_Table__InsertedTwoElements__DeletesBoth" << std::endl;
}
