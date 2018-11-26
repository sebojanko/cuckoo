#include <iostream>
#include <assert.h>
#include "../table.h"

void test_Table__InsertedOneElement__FindsOneElement() {
    Table t = Table();
    t.Insert(1);
    assert(t.Contains(1));
    std::cout << "PASS test_Table__InsertedOneElement__FindsOneElement" << std::endl;
}

void test_Table__InsertedOneElement__SearchForAnother() {
    Table t = Table();
    t.Insert(1);
    assert(!t.Contains(2));
    std::cout << "PASS test_Table__InsertedOneElement__SearchForAnother" << std::endl;
}

void test_Table__InsertedTwoElements__FindsBoth() {
    Table t = Table();
    t.Insert(1);
    t.Insert(2);
    assert(t.Contains(1));
    assert(t.Contains(2));
    std::cout << "PASS test_Table__InsertedTwoElements__FindsBoth" << std::endl;
}

void test_Table__InsertedOneElement__DeletesOneElement() {
    Table t = Table();
    t.Insert(1);
    assert(t.Remove(1));
    assert(!t.Contains(1));
    std::cout << "PASS test_Table__InsertedOneElement__DeletesOneElement" << std::endl;
}

void test_Table__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement() {
    Table t = Table();
    t.Insert(1);
    assert(!t.Remove(2));
    assert(t.Contains(1));
    std::cout << "PASS test_Table__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement" << std::endl;
}

void test_Table__InsertedTwoElements__DeletesBoth() {
    Table t = Table();
    t.Insert(1);
    t.Insert(2);
    assert(t.Remove(1));
    assert(t.Remove(2));
    assert(!t.Contains(1));
    assert(!t.Contains(2));
    std::cout << "PASS test_Table__InsertedTwoElements__DeletesBoth" << std::endl;
}
