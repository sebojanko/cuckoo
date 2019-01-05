#include "TableTests.cpp"
#include "BucketTests.cpp"
#include "KMerGeneratorTests.cpp"
#include "SimpleEncoderTests.cpp"
#include "CompactTableTests.cpp"

std::string getKMerDataInputArg(int argc, const char* argv[]) {
  if (argc < 2) {
        std::cout << "Missing input KMer file argument." << std::endl;
        exit(-1);
    }
  return argv[1];
}

int main(int argc, const char* argv[]) {

    test_SimpleEncoder__EncodeSingleChar();
    test_SimpleEncoder__EncodeKMer();
    test_SimpleEncoder__EncodeBigValue();
    test_SimpleEncoder__EncodeMaxValue();
    test_SimpleEncoder__DecodeSingleChar();
    test_SimpleEncoder__DecodeKMer();
    test_SimpleEncoder__DecodeBigValue();
    test_SimpleEncoder__DecodeMaxValue();
    test_SimpleEncoder__EncodeDecode();

    test_CompactTable__InsertedOneElement__FindsOneElement();
    test_CompactTable__InsertedOneElement__SearchForAnother();
    test_CompactTable__InsertedTwoElements__FindsBoth();
    test_CompactTable__InsertedOneElement__DeletesOneElement();
    test_CompactTable__InsertedOneElement__UnsuccessfulDeletionOfNonExistingElement();
    test_CompactTable__InsertedTwoElements__DeletesBoth();
    test_CompactTable__InsertedSameElementTwice__DeletesBoth();
    test_CompactTable__InsertedSameElementTwice__DeletesThree();
    test_CompactTable__OverfillBucket();
    test_CompactTable__OverfillBucket__DeleteAll();

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

    if (argc == 2) {
        std::string filename{getKMerDataInputArg(argc, argv)};

        test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength10(filename);
        test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength1(filename);
        test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength100(filename);
        test_KMerGenerator__ExtractRandomKMer__ReturnsStringOfLength500(filename);
    }

    return 0;
}
