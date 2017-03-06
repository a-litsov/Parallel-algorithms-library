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

int p = 3;

inline int rehash(char a, char b, int h, int d) {
    int result = (((h - a*d)*p) + b); // hash mat be huge, so we keep it in [0..INT_MAX]
    return result;
}

std::vector<size_t> RabinKarpAlgorithm(const char *t, const char *s, int n, int m) {
    std::vector<size_t> positions;
#pragma omp parallel
{
    std::vector<size_t> pos_private;
    int tid = omp_get_thread_num();
    int threadsCount = omp_get_num_threads();
    int threadPortion = n / threadsCount;
    int start = tid * threadPortion, end = std::min((tid+1)*threadPortion + (m-1), n);
    int d = pow(p, m-1);
    int ht, hs;
    ht = hs = 0;
    int i;
    for (i = 0; i < m; i++) {
        hs = ( ( hs * p ) + s[i] );
        ht = ( ( ht * p ) + t[i + start] );
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
