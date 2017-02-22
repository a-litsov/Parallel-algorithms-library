//
//  Other.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include "Other.h"

std::string generateRandomString(size_t len, std::string s, std::vector<size_t> *positions) {
    srand(time(0));
    std::string str = "abcdefghijklmnopqrstuvwxyz";
    std::string newstr;
    int pos;
    while(newstr.size() < len) {
        pos = ((rand() % (str.size() - 1)));
        newstr += str.substr(pos,1);
        if (s.size() != 0 && rand() % 5 == 2) {
            positions->push_back(newstr.size());
            newstr += s;
        }
    }
    return newstr;
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
