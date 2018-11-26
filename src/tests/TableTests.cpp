#include <iostream>
#include <assert.h>
#include "../table.h"

void test_CheckInsertion__InsertedOneElement__FindsOneElement(Table t) {
    t.Insert(1);
    assert(t.Contains(1));
}

void test_CheckInsertion__InsertedOneElement__SearchForAnother(Table t) {
    t.Insert(1);
    assert(!t.Contains(2));
}

void test_CheckInsertion__InsertedTwoElements__FindsBoth(Table t) {
    t.Insert(1);
    t.Insert(2);
    assert(t.Contains(1));
    assert(t.Contains(2));
}

void test_CheckDeletion__InsertedOneElement__DeletesOneElement(Table t) {
    t.Insert(1);
    assert(t.Remove(1));
    assert(!t.Contains(1));
}

void test_CheckDeletion__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement(Table t) {
    t.Insert(1);
    assert(!t.Remove(2));
    assert(t.Contains(1));
}

void test_CheckDeletion__InsertedTwoElements__DeletesBoth(Table t) {
    t.Insert(1);
    t.Insert(2);
    assert(t.Remove(1));
    assert(t.Remove(2));
    assert(!t.Contains(1));
    assert(!t.Contains(2));
}

int main() {
    Table t = Table();

    test_CheckInsertion__InsertedOneElement__FindsOneElement(t);
    test_CheckInsertion__InsertedOneElement__SearchForAnother(t);
    test_CheckInsertion__InsertedTwoElements__FindsBoth(t);

    test_CheckDeletion__InsertedOneElement__DeletesOneElement(t);
    test_CheckDeletion__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement(t);
    test_CheckDeletion__InsertedTwoElements__DeletesBoth(t);
    return 0;
}

