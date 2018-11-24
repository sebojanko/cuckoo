//
// Created by sebo on 11/24/18.
//

#define BOOST_TEST_MODULE Simple testcases
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(simple_test) {
    BOOST_CHECK_EQUAL(2+2, 4);
}

//https://www.jetbrains.com/help/clion/boost-test-support.html
