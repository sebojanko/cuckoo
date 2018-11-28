#include <iostream>
#include <assert.h>
#include "../Bucket.h"

void test_Bucket__InsertedOneElement__RetrievesFirst() {
    Bucket b = Bucket();
    b.Push("test");
    assert(b.Get(0) == "test");
    std::cout << "PASS test_Bucket__InsertedOneElement__RetrievesFirst" << std::endl;
}

void test_Bucket__InsertedFiveElements__RetrievesLast() {
    Bucket b = Bucket();
    b.Push("1");
    b.Push("2");
    b.Push("3");
    b.Push("4");
    b.Push("5");
    assert(b.Get(4) == "5");
    std::cout << "PASS test_Bucket__InsertedFiveElements__RetrievesLast" << std::endl;
}

void test_Bucket__InsertedFiveElements__RetrievesThird() {
    Bucket b = Bucket();
    b.Push("1");
    b.Push("1");
    b.Push("1");
    b.Push("1");
    b.Push("1");
    assert(b.Get(2) == "1");
    std::cout << "PASS test_Bucket__InsertedFiveElements__RetrievesThird" << std::endl;
}

void test_Bucket__InsertedTwoElements__FailsToRetrieveThird() {
    Bucket b = Bucket();
    b.Push("1");
    b.Push("2");
    assert(b.Get(2) != "2");
    std::cout << "PASS test_Bucket__InsertedTwoElements__FailsToRetrieveThird" << std::endl;
}

void test_Bucket__InsertedTwoElements__FailsToRetrieveMinusFirst() {
    Bucket b = Bucket();
    b.Push("1");
    b.Push("2");
    assert(b.Get(-1) != "2");
    std::cout << "PASS test_Bucket__CheckPush__InsertedTwoElements__FailsToRetrieveMinusFirst" << std::endl;
}
