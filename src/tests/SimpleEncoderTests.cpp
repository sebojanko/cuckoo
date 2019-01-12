#include <iostream>
#include <assert.h>
#include "../SimpleEncoder.h"

// created by David on 18/12/18

void test_SimpleEncoder__EncodeSingleChar() {
    SimpleEncoder enc;
    assert(enc.Encode("A") == 32ULL);
    assert(enc.Encode("C") == 33ULL);
    assert(enc.Encode("G") == 34ULL);
    assert(enc.Encode("T") == 35ULL);
    std::cout << "PASS test_SimpleEncoder__EncodeSingleChar" << std::endl;
}

void test_SimpleEncoder__EncodeKMer() {
    SimpleEncoder enc;
    uint64_t encoded = enc.Encode("CACAGT");
    assert(encoded == 1081875ULL);
    std::cout << "PASS test_SimpleEncoder__EncodeKMer" << std::endl;
}

void test_SimpleEncoder__EncodeBigValue() {
    SimpleEncoder enc;
    uint64_t encoded = enc.Encode("ACGTACGTACGTACGT");
    assert(encoded == 1131605016260691ULL);
    std::cout << "PASS test_SimpleEncoder__EncodeBigValue" << std::endl;
}

void test_SimpleEncoder__EncodeMaxValue() {
    SimpleEncoder enc;
    uint64_t encoded1, encoded2;
    encoded1 = enc.Encode("ACGTACGTACGTACGTACGT");
    assert(encoded1 == 4635054146603790419ULL);
    encoded2 = enc.Encode("ACGTACGTACGTACGTACGTA");
    assert(encoded1 == encoded2);
    std::cout << "PASS test_SimpleEncoder__EncodeMaxValue" << std::endl;
}

void test_SimpleEncoder__DecodeSingleChar() {
    SimpleEncoder enc;
    assert(enc.Decode(32ULL) == "A");
    assert(enc.Decode(33ULL) == "C");
    assert(enc.Decode(34ULL) == "G");
    assert(enc.Decode(35ULL) == "T");
    std::cout << "PASS test_SimpleEncoder__DecodeSingleChar" << std::endl;
}

void test_SimpleEncoder__DecodeKMer() {
    SimpleEncoder enc;
    std::string decoded = enc.Decode(1048659ULL);
    assert(decoded == "AAACGT");
    std::cout << "PASS test_SimpleEncoder__DecodeKMer" << std::endl;
}

void test_SimpleEncoder__DecodeBigValue() {
    SimpleEncoder enc;
    std::string decoded = enc.Decode(1125899906842627ULL);
    assert(decoded == "AAAAAAAAAAAAAAAT");
    std::cout << "PASS test_SimpleEncoder__DecodeBigValue" << std::endl;
}

void test_SimpleEncoder__DecodeMaxValue() {
    SimpleEncoder enc;
    std::string decoded = enc.Decode(4899916394579099651ULL);
    assert(decoded == "GAAAAAAAAAAAAAAAAAAT");
    std::cout << "PASS test_SimpleEncoder__DecodeMaxValue" << std::endl;
}

void test_SimpleEncoder__EncodeDecode() {
    SimpleEncoder enc;
    uint64_t encoded = enc.Encode("AAACGTACGT");
    assert(enc.Decode(encoded) == "AAACGTACGT");
    std::cout << "PASS test_SimpleEncoder__EncodeDecode" << std::endl;
}


