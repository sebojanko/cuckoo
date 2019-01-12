#include <iostream>
#include <assert.h>
#include "../Hash.h"

// created by David on 10/1/19

void test_Hasher__Integer_TIMS() {
    Hasher hasher(8, Hash::TIMS);
    uint64_t h1 = hasher.hash(1ULL);
    uint64_t h2 = hasher.hash(2ULL);
    uint64_t h3 = hasher.hash(33ULL);
    // just check for inequality since i have to official TIMS generator
    assert(h1 != h2);
    assert(h1 != h3);
    assert(h2 != h3);
    std::cout << "PASS test_Hasher__Integer_TIMS" << std::endl;
}

void test_Hasher__Integer_MD5() {
    Hasher hasher(8, Hash::MD5);
    uint64_t h1 = hasher.hash(1ULL);
    uint64_t h2 = hasher.hash(2ULL);
    uint64_t h3 = hasher.hash(123412341234ULL);
    // md5: c4ca4238a0b923820dcc509a6f75849b
    assert(h1 == 14180219187711517570ULL);
    // md5: c81e728d9d4c2f636f067f89cc14862c
    assert(h2 == 14420089009441877859ULL);
    // md5: 4d3daeeb3ea3d90d4d6e7a20a5b483a9
    assert(h3 == 5565797039891273997ULL);
    std::cout << "PASS test_Hasher__Integer_MD5" << std::endl;
}

void test_Hasher__Integer_SHA1() {
    Hasher hasher(8, Hash::SHA1);
    uint64_t h1 = hasher.hash(1ULL);
    uint64_t h2 = hasher.hash(2ULL);
    uint64_t h3 = hasher.hash(123412341234ULL);
    // sha1: 356a192b7913b04c54574d18c28d46e6395428ab
    assert(h1 == 3848916506047131724ULL);
    // sha1: da4b9237bacccdf19c0760cab7aec4a8359010b0
    assert(h2 == 15729826891576430065ULL);
    // sha1: 5a78babbb162531b3a16c55310a4e7228d68f2e9
    assert(h3 == 6519165775916454683ULL);
    std::cout << "PASS test_Hasher__Integer_SHA1" << std::endl;
}

void test_Hasher__Integer_STL() {
    Hasher hasher(8, Hash::STL);
    uint64_t h1 = hasher.hash(1ULL);
    uint64_t h2 = hasher.hash(2ULL);
    uint64_t h3 = hasher.hash(123412341234ULL);
    assert(h1 == 1ULL);
    assert(h2 == 2ULL);
    assert(h3 == 123412341234ULL);
    std::cout << "PASS test_Hasher__Integer_STL" << std::endl;
}

void test_Hasher__Integer_IDENTITY() {
    Hasher hasher(8, Hash::STL);
    uint64_t h1 = hasher.hash(1ULL);
    uint64_t h2 = hasher.hash(2ULL);
    uint64_t h3 = hasher.hash(123412341234ULL);
    assert(h1 == 1ULL);
    assert(h2 == 2ULL);
    assert(h3 == 123412341234ULL);
    std::cout << "PASS test_Hasher__Integer_IDENTITY" << std::endl;
}

void test_Hasher__String_TIMS() {
    // 20-mer
    std::string e1("ACGTACGTACGTACGTACGT");
    std::string e2("ACGTACGTACGTACGTACGG"); // last char diff (T-G)
    Hasher hasher(8, Hash::TIMS);
    uint64_t h1 = hasher.hash(e1);
    uint64_t h2 = hasher.hash(e2);
    // just check for inequality since i have to official TIMS generator
    assert(h1 != h2);

    // 40-mer, more than what the encoder can handle
    // should give same result
    e1 = "ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT";
    e2 = "ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGG";
    h1 = hasher.hash(e1);
    h2 = hasher.hash(e2);
    assert(h1 == h2);
    std::cout << "PASS test_Hasher__String_TIMS" << std::endl;
}

void test_Hasher__String_MD5() {
    // 40-mer, last char diff (G-T)
    std::string e1("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT");
    std::string e2("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGG");
    Hasher hasher(8, Hash::MD5);
    uint64_t h1 = hasher.hash(e1);
    assert(h1 == 10991465385735211093ULL);
    uint64_t h2 = hasher.hash(e2);
    assert(h2 == 1804265520071240556ULL);
    std::cout << "PASS test_Hasher__String_MD5" << std::endl;
}

void test_Hasher__String_SHA1() {
    // 40-mer, last char diff (G-T)
    std::string e1("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT");
    std::string e2("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGG");

    Hasher hasher(8, Hash::SHA1);
    uint64_t h1 = hasher.hash(e1);
    assert(h1 == 5794984960110568035ULL);
    uint64_t h2 = hasher.hash(e2);
    assert(h2 == 1960348096402318606ULL);
    std::cout << "PASS test_Hasher__String_SHA1" << std::endl;
}

void test_Hasher__String_STL() {
    // 40-mer, last char diff (G-T)
    std::string e1("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT");
    std::string e2("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGG");

    Hasher hasher(8, Hash::STL);
    uint64_t h1 = hasher.hash(e1);
    uint64_t h2 = hasher.hash(e2);
    assert(h1 == std::hash<std::string>{}(e1));
    assert(h2 == std::hash<std::string>{}(e2));
    std::cout << "PASS test_Hasher__String_STL" << std::endl;
}

void test_Hasher__String_IDENTITY() {
    // 40-mer, last char diff (G-T)
    std::string e1("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT");
    std::string e2("ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGG");

    SimpleEncoder encoder;
    uint64_t enc1 = encoder.Encode(e1);
    uint64_t enc2 = encoder.Encode(e2);

    Hasher hasher(8, Hash::IDENTITY);
    uint64_t h1 = hasher.hash(e1);
    uint64_t h2 = hasher.hash(e2);
    assert(h1 == enc1);
    assert(h2 == enc2);
    assert(h1 == h2);

    // 20-mer
    e1 = "ACGTACGTACGTACGTACGT";
    e2 = "ACGTACGTACGTACGTACGG"; // last char diff (T-G)
    enc1 = encoder.Encode(e1);
    enc2 = encoder.Encode(e2);
    h1 = hasher.hash(e1);
    h2 = hasher.hash(e2);
    assert(h1 == enc1);
    assert(h2 == enc2);
    assert(h1 != h2);
    std::cout << "PASS test_Hasher__String_IDENTITY" << std::endl;
}
