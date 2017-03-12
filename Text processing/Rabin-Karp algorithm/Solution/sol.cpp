//
//  sol.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//
#include "sol.h"

#include <math.h>
#include <omp.h>


int p = 33;
int maxValue = 103000111;

inline long rehash(char a, char b, long h, long d) {
    long result = (((h - a*d)*p) + b) % maxValue;
    if(result < 0)
        result = result + maxValue;
    return result;
}

long myPow (long x, long p) {
    long i = 1;
    for (long j = 1; j <= p; j++)  i = (i * x) % maxValue;
    return i;
}

std::vector<long> RabinKarpAlgorithm(std::string text, std::string pattern) {
    std::vector<long> positions;
    size_t n = text.size();
    size_t m = pattern.size();
#pragma omp parallel
{
    std::vector<long> pos_private;
    size_t tid = omp_get_thread_num();
    size_t threadsCount = omp_get_num_threads();
    size_t threadPortion = n / threadsCount;
    size_t start = tid * threadPortion, end = (tid == threadsCount-1) ? n : (tid+1)*threadPortion + (m-1);
    long d = myPow(p, m-1);
    long ht, hs;
    ht = hs = 0;
    size_t i;
    
    /* Hashing pattern and first pattern.size symbols in text string */
    for (i = 0; i < m; i++) {
        hs = ((hs * p) + pattern[i]) % maxValue;
        ht = ((ht * p) + text[i + start]) % maxValue;
    }
    
    /* Searching */
    for (i = m+start; i <= end; i++) {
        if (ht == hs && text.substr(i-m, m) ==  pattern)
            pos_private.push_back(i - m);
        ht = rehash(text[i-m], text[i], ht, d);
    }
#pragma omp critical
    positions.insert(positions.end(), pos_private.begin(), pos_private.end());
}
    std::sort(positions.begin(), positions.end());
    return positions;
}
