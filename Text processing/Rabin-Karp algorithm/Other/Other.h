//
//  Other.h
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#ifndef Other
#define Other

#include <vector>
#include <string>
#include <time.h>
#include <math.h>
#include <time.h>
#include <random>

std::string generateRandomString(size_t len, std::string s = "", std::vector<size_t> *positions = 0);
std::vector<size_t> getAllOccurences(std::string str, std::string sub);

#endif /* Other_h */
