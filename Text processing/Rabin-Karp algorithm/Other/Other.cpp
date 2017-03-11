//
//  Other.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include "Other.h"
#include <string>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

// returns randomly generated string with length equals to value stored in 'length' argument
std::string generateRandomString(size_t length) {
    srand(static_cast<unsigned int>(time(0)));
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz", result = "";
    for(int i = 0; i < length; i++) {
        result += alphabet[rand() % alphabet.size()];
    }
    return result;
}

// returns randomly generated string (with size of 'length' or random size otherwise) where probability defines how often pattern will be met (0-1)
// returns randomly generated pattern-string through argument 'pattern' if it's not set
// returns vector<int> with pattern positions in generated string through argument 'positions'
std::string generateRandomStringByPattern(std::string &pattern, std::vector<long> *positions, size_t length, double probability ) {
    srand(static_cast<unsigned int>(time(0)));
    // if length is not set then we set it equals random number in [1, max_length]
    int max_length = 10000;
    if (length == 0)
        length = rand() % max_length + 1;
    // if pattern-string not set
    int coef = 20; // how many times pattern.length smaller than text.length
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz", result = "";
    size_t patternSize = pattern.size();
    switch(patternSize) {
        // if pattern string is not set we just randomly generate it
        case 0:
            pattern = generateRandomString(rand() % length/coef + 1);
            break;
        // if pattern string consist of only one symbol we remove it from our alphabet to escape from unexpected occurences
        case 1:
            alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), pattern[0]), alphabet.end());
            break;
        // in all other cases we just don't touch our pattern string (because user specified it by his own)
    }
    
    int pos;
    while(result.size() < length) {
        pos = rand() % alphabet.size();
        result += alphabet[pos];
        if (dis(gen) < probability && result.size() + pattern.size() <= length) {
            if(positions != 0)
                positions->push_back(result.size());
            result += pattern;
        }
    }
    return result;
}

std::vector<long> getAllOccurences(std::string str, std::string sub) {
    std::vector<long> positions; // holds all the positions that sub occurs within str
    
    if (sub == "")
        return positions;
    long pos = str.find(sub, 0);
    while(pos != std::string::npos)
    {
        positions.push_back(pos);
        pos = str.find(sub,pos+1);
    }
    return positions;
}
