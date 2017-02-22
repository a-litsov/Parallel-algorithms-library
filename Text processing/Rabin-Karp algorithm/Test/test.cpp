//
//  main.cpp
//  Rabin-Karp algorithm
//
//  Created bt al1as on 21/02/17.
//  Coptright © 2017 al1as. All rights reserved.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <iostream>
#include <omp.h>
#include <math.h>
#include <vector>
#include "catch.hpp"

#include "../Solution/sol.h"
#include "../Other/Other.h"


TEST_CASE( "Substring finded at start", "[Rabin-Karp algorithm]" ) {
    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtu";
    std::string s = "hello";
    REQUIRE( RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size()) == getAllOccurences(t, s));
}

TEST_CASE( "Substring finded at end", "[Rabin-Karp algorithm]" ) {
    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtupattern";
    std::string s = "pattern";
    REQUIRE( RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size()) == getAllOccurences(t, s));
}

TEST_CASE( "Random char finded", "[Rabin-Karp algorithm]" ) {
    std::string t = "oahsnhohellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtuphuosnattern";
    std::string s = generateRandomString(1);
    REQUIRE( RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size()) == getAllOccurences(t, s));
}

TEST_CASE( "Many occurences case", "[Rabin-Karp algorithm]" ) {
    std::string s = "pattern";
    std::string t = "hellouaotstn" + s + "ahothstnheao" + s + "thnhthkt" + s + "haeosutn" + s + "hththaestnu" + s + s + s + "h" + s + "hygsaseohtupattern";
    REQUIRE( RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size()) == getAllOccurences(t, s));
}

TEST_CASE( "Equal string case", "[Rabin-Karp algorithm]" ) {
    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtupattern";
    std::string s = t;
    REQUIRE( RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size()) == getAllOccurences(t, s));
}




