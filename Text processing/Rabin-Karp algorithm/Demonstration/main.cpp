//
//  main.cpp
//  Demonstration
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <vector>

#include "../Solution/sol.h"
#include "../Other/Other.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::string t, s;
    size_t length;
    std::cout << "Enter S string(pattern) size:";
    std::cin >> length;
    s = generateRandomString(length);
    
    std::cout << "Enter T string(text) size:";
    std::cin >> length;
    std::vector<size_t> rightPositions, positions;
    t = generateRandomStringByPattern(s, &rightPositions, length);
    
    positions = RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size(), s.size());
    
    std::cout << "All is done! Result is:";
    std::cout << (positions == rightPositions);
    std::cout << "\nOccurences count:" << rightPositions.size() << "\n";
    
    return 0;
}
