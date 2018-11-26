#include "TableTests.cpp"
#include "BucketTests.cpp"

int main() {
    test_Table__InsertedOneElement__FindsOneElement();
    test_Table__InsertedOneElement__SearchForAnother();
    test_Table__InsertedTwoElements__FindsBoth();

    test_Table__InsertedOneElement__DeletesOneElement();
    test_Table__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement();
    test_Table__InsertedTwoElements__DeletesBoth();


    test_Bucket__InsertedOneElement__RetrievesFirst();
	test_Bucket__InsertedFiveElements__RetrievesLast();
	test_Bucket__InsertedFiveElements__RetrievesThird();
	test_Bucket__InsertedTwoElements__FailsToRetrieveThird();
	test_Bucket__InsertedTwoElements__FailsToRetrieveMinusFirst();

    return 0;
}
