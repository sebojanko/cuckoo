#include "TableTests.cpp"
#include "BucketTests.cpp"
#include "KMerGeneratorTests.cpp"
#include "SimpleEncoderTests.cpp"

int main() {
    test_SimpleEncoder__EncodeSingleChar();
    test_SimpleEncoder__EncodeKMer();
    test_SimpleEncoder__EncodeBigValue();
    test_SimpleEncoder__EncodeMaxValue();
    test_SimpleEncoder__DecodeSingleChar();
    test_SimpleEncoder__DecodeKMer();
    test_SimpleEncoder__DecodeBigValue();
    test_SimpleEncoder__DecodeMaxValue();
    test_SimpleEncoder__EncodeDecode();

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

    test_Bucket__InsertedOneElement__RetrievesFirstWithOverloadedOperator();
    test_Bucket__InsertedFiveElements__RetrievesLastWithOverloadedOperator();
    test_Bucket__InsertedFiveElements__RetrievesThirdWithOverloadedOperator();
    test_Bucket__InsertedTwoElements__FailsToRetrieveThirdWithOverloadedOperator();
    test_Bucket__InsertedTwoElements__FailsToRetrieveMinusFirstWithOverloadedOperator();

    
    test_KMerGenerator__GenerateRandom10Mer__ReturnsStringOfLength10();
    test_KMerGenerator__GenerateRandom1Mer__ReturnsStringOfLength1();
    test_KMerGenerator__GenerateRandom100Mer__ReturnsStringOfLength100();
    test_KMerGenerator__GenerateRandom500Mer__ReturnsStringOfLength500();

    test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength10();
    test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength1();
    test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength100();
    test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength500();

    return 0;
}
