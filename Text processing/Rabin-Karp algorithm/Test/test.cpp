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
#include <string>

#include "../Solution/sol.h"
#include "../Other/Other.h"

int threadsNum = 4;

TEST_CASE("Substring finded at start", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);
    
    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtu";
    std::string s = "hello";
    std::vector<size_t> result = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    std::sort(result.begin(), result.end());
    REQUIRE( result == getAllOccurences(t, s));
}

TEST_CASE("Substring finded at end", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtupattern";
    std::string s = "pattern";
    std::vector<size_t> result = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    std::sort(result.begin(), result.end());
    REQUIRE( result == getAllOccurences(t, s));
}

TEST_CASE("Random char finded", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::string t = "oahsnhohellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtuphuosnattern";
//    std::string s = generateRandomString(1);
    std::string s = "h";
    std::cout << s;
    std::vector<size_t> result = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    std::sort(result.begin(), result.end());
    REQUIRE( result == getAllOccurences(t, s));
}

TEST_CASE("Many occurences case", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::string s = "pattern";
    std::string t = "hellouaotstn" + s + "ahothstnheao" + s + "thnhthkt" + s + "haeosutn" + s + "hththaestnu" + s + s + s + "h" + s + "hygsaseohtupattern";
    std::vector<size_t> result = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    std::sort(result.begin(), result.end());
    REQUIRE( result == getAllOccurences(t, s));
}

TEST_CASE("Equal string case", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::string t = "hellouaotstnahothstnheaothnhthkthaeosutnhththaestnuhygsaseohtupattern";
    std::string s = t;
    std::vector<size_t> result = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    std::sort(result.begin(), result.end());
    REQUIRE( result == getAllOccurences(t, s));
}

TEST_CASE("Random case 1", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::vector<size_t> rightPositions, positions;
    srand(static_cast<unsigned int>(time(0)));
    std::string pattern;
    std::string t = generateRandomStringByPattern(pattern, &rightPositions);
    
    positions = RabinKarpAlgorithm(t.c_str(), pattern.c_str(), t.size(), pattern.size());
    std::sort(positions.begin(), positions.end());
    REQUIRE(positions == rightPositions);
}

TEST_CASE("Random case 2 - 10k text size", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::vector<size_t> rightPositions, positions;
    srand(static_cast<unsigned int>(time(0)));
    std::string pattern;
    int textSize = 10000;
    std::string t = generateRandomStringByPattern(pattern, &rightPositions, textSize);
    
    positions = RabinKarpAlgorithm(t.c_str(), pattern.c_str(), t.size(), pattern.size());
    std::sort(positions.begin(), positions.end());
    REQUIRE(positions == rightPositions);
}

TEST_CASE("Random case 3 - 20k text size", "[Rabin-Karp algorithm]") {
    omp_set_num_threads(threadsNum);

    std::vector<size_t> rightPositions, positions;
    srand(static_cast<unsigned int>(time(0)));
    std::string pattern;
    int textSize = 20000;
    std::string t = generateRandomStringByPattern(pattern, &rightPositions, textSize);
    
    positions = RabinKarpAlgorithm(t.c_str(), pattern.c_str(), t.size(), pattern.size());
    std::sort(positions.begin(), positions.end());
    REQUIRE(positions == rightPositions);
}
