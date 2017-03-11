//
//  main.cpp
//  generator
//
//  Created by al1as on 29/01/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include "../Other/Other.h"

#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

size_t testsCount = 10;
size_t patternLengthRange[] = {50, 2000};
size_t textStartSize = 100000;
size_t textStepSize = 100000;

using namespace std;

int main()
{
    for(int i = 0; i < testsCount; i++) {
        ofstream outfile(to_string(i+1) + ".in", ofstream::binary);
        size_t patternLength = rand() % (patternLengthRange[1] - patternLengthRange[0] + 1) + patternLengthRange[0];
        std::string pattern = generateRandomString(patternLength);
        outfile.write(pattern.c_str(), pattern.size() + 1);
        
        vector<long> positions;
        size_t textSize = textStartSize + i*textStepSize;
        std::string text = generateRandomStringByPattern(pattern, 0, textSize);
        outfile.write(text.c_str(), text.size() + 1);
        outfile.close();
    }
    return 0;
}
