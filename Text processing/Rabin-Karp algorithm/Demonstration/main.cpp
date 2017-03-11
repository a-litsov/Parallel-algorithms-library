//
//  main.cpp
//  Demonstration
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <vector>
#include <omp.h>

#include "../Solution/sol.h"
#include "../Other/Other.h"


int main(int argc, const char * argv[]) {
    std::vector<long> rightPositions, positions;
    std::string t, s;
    size_t length;
    std::cout << "Enter S string(pattern) size:";
    std::cin >> length;
    s = generateRandomString(length);
    
    std::cout << "Enter T string(text) size:";
    std::cin >> length;
    t = generateRandomStringByPattern(s, &rightPositions, length);
    
    double seqTime = 0;
    double parTime = 0;
    
    int threadsCount = 1;
    do {
        std::cout << "Enter threads count:";
        std::cin >> threadsCount;
        omp_set_num_threads(threadsCount);
        
        double start = omp_get_wtime();
        positions = RabinKarpAlgorithm(t, s);
        double end = omp_get_wtime();
        
        std::cout << "All is done! Result is:";
        std::sort(positions.begin(), positions.end());
        std::cout << (positions == rightPositions);
        std::cout << "\nOccurences count:" << rightPositions.size() << "\n";
        std::cout << "Time is" << end - start << std::endl;
        
        if (threadsCount == 1)
            seqTime = end - start;
        else {
            parTime = end - start;
            std::cout << "Acceleration factor is: " << seqTime/parTime << "\n";
        }
            
        
        positions.clear();
    } while(threadsCount != 0);
    return 0;
}
