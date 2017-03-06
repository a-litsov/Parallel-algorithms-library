//
//  Other.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include "Other.h"
#include <string>

// returns randomly generated string with length equals to value stored in 'length' argument
std::string generateRandomString(int length) {
    srand(static_cast<unsigned int>(time(0)));
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz", result = "";
    for(int i = 0; i < length; i++) {
        result += alphabet[rand() % alphabet.size()];
    }
    return result;
}

// returns randomly generated string (with size of 'length' or random size otherwise) which may include pattern-string random amount of times
// returns randomly generated pattern-string through argument 'pattern' if it's not set
// returns vector<int> with pattern positions in generated string through argument 'positions'
std::string generateRandomStringByPattern(std::string &pattern, std::vector<size_t> *positions, size_t length) {
    srand(static_cast<unsigned int>(time(0)));
    // if length is not set then we set it equals random number in [1, max_length]
    int max_length = 10000;
    if (length == 0)
        length = rand() % max_length + 1;
    // if pattern-string not set
    int coef = 8; // how many times pattern.length smaller than text.length
    if (pattern.size() == 0)
        pattern = generateRandomString(rand() % length/coef + 1);
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz", result = "";
    int pos;
    while(result.size() < length) {
        pos = rand() % alphabet.size();
        result += alphabet[pos];
        if (rand() %  length < length/2 && result.size() + pattern.size() <= length) {
            positions->push_back(result.size());
            result += pattern;
        }
    }
    return result;
}

std::vector<size_t> getAllOccurences(std::string str, std::string sub) {
    std::vector<size_t> positions; // holds all the positions that sub occurs within str
    
    if (sub == "")
        return positions;
    size_t pos = str.find(sub, 0);
    while(pos != std::string::npos)
    {
        positions.push_back(pos);
        pos = str.find(sub,pos+1);
    }
    return positions;
}
