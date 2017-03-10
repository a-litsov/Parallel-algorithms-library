//
//  sol.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 22/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//
#include "sol.h"

#include <math.h>
#include <vector>
#include <omp.h>

int p = 33;
int max_value = 103000111;

inline long rehash(char a, char b, long h, long d) {
    long result = (((h - a*d)*p) + b) % max_value;
    if(result < 0)
        result = result + max_value;
    return result;
}

long myPow (long x, long p) {
    long i = 1;
    for (long j = 1; j <= p; j++)  i = (i * x) % max_value;
    return i;
}

std::vector<long> RabinKarpAlgorithm(const char *t, const char *s, size_t n, size_t m) {
    std::vector<long> positions;
#pragma omp parallel
{
    std::vector<long> pos_private;
    int tid = omp_get_thread_num();
    int threadsCount = omp_get_num_threads();
    int threadPortion = n / threadsCount;
    int start = tid * threadPortion, end = std::min((tid+1)*threadPortion + (m-1), n);
    long d = myPow(p, m-1);
    long ht, hs;
    ht = hs = 0;
    int i;
    for (i = 0; i < m; i++) {
        hs = ( ( hs * p ) + s[i] ) % max_value;
        ht = ( ( ht * p ) + t[i + start] ) % max_value;
    }
    /* Searching */

    for (i=m; i <= end-start; i++) {
        if (ht == hs && memcmp(&t[ i+start-m ], s, m) == 0)
            pos_private.push_back(i + start - m);
        ht = rehash(t[i+start-m], t[i+start], ht, d);
    }
#pragma omp critical
    positions.insert(positions.end(), pos_private.begin(), pos_private.end());
}
    return positions;
}
