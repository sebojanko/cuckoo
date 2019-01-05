//
// Created by David (cizl) on 1/4/19.
//
#include <iostream>
#include <assert.h>
#include "../CompactTable.h"
#include "../Hash.h"

void test_CompactTable__InsertedOneElement__FindsOneElement() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    assert(t.Contains(1));
    std::cout << "PASS test_CompactTable__InsertedOneElement__FindsOneElement" << std::endl;
}

void test_CompactTable__InsertedOneElement__SearchForAnother() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    assert(!t.Contains(2));
    std::cout << "PASS test_CompactTable__InsertedOneElement__SearchForAnother" << std::endl;
}

void test_CompactTable__InsertedTwoElements__FindsBoth() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    t.Insert(2);
    assert(t.Contains(1));
    assert(t.Contains(2));
    std::cout << "PASS test_CompactTable__InsertedTwoElements__FindsBoth" << std::endl;
}

void test_CompactTable__InsertedOneElement__DeletesOneElement() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    assert(t.Contains(1));
    assert(t.Remove(1));
    assert(!t.Contains(1));
    std::cout << "PASS test_CompactTable__InsertedOneElement__DeletesOneElement" << std::endl;
}

void test_CompactTable__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    assert(!t.Remove(2));
    assert(t.Contains(1));
    std::cout << "PASS test_CompactTable__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement" << std::endl;
}

void test_CompactTable__InsertedTwoElements__DeletesBoth() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    t.Insert(2);
    assert(t.Contains(1));
    assert(t.Contains(2));
    assert(t.Remove(1));
    assert(t.Remove(2));
    assert(!t.Contains(1));
    assert(!t.Contains(2));
    std::cout << "PASS test_CompactTable__InsertedTwoElements__DeletesBoth" << std::endl;
}

void test_CompactTable__InsertedSameElementTwice__DeletesBoth() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    t.Insert(1);
    assert(t.Contains(1));
    assert(t.Remove(1));
    assert(t.Contains(1));
    assert(t.Remove(1));
    assert(!t.Contains(1));
    std::cout << "PASS test_CompactTable__InsertedSameElementTwice__DeletesBoth" << std::endl;
}

void test_CompactTable__InsertedSameElementTwice__DeletesThree() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    t.Insert(1);
    t.Insert(1);
    assert(t.Remove(1));
    assert(t.Remove(1));
    assert(!t.Contains(1));
    assert(!t.Remove(1));
    std::cout << "PASS test_CompactTable__InsertedSameElementTwice__DeletesThree" << std::endl;
}

void test_CompactTable__OverfillBucket() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    for (int i = 0; i < 10; i++) {
        t.Insert(1);
    }
    assert(t.Contains(1));
    std::cout << "PASS test_CompactTable__OverfillBucket" << std::endl;
}

void test_CompactTable__OverfillBucket__DeleteAll() {
    Hasher hasher(8);
    CompactTable t = CompactTable(&hasher);
    for (int i = 0; i < 10; i++) {
        t.Insert(1);
    }
    for (int i = 0; i < 10; i++) {
        assert(t.Remove(1));
    }
    assert(!t.Contains(1));
    std::cout << "PASS test_CompactTable__OverfillBucket__DeleteAll" << std::endl;
}
