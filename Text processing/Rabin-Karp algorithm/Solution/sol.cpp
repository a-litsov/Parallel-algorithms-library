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

int p = 2;

inline int rehash(char a, char b, int h, int d) {
    int result = (((h - a*d)*p) + b); // hash mat be huge, so we keep it in [0..INT_MAX]
    return result;
}

std::vector<size_t> RabinKarpAlgorithm(const char *t, const char *s, size_t n, size_t m) {
    std::vector<size_t> positions;
    size_t i;
    int d = pow(p, m-1);
    int ht, hs;
    ht = hs = 0;
    for (i = 0; i < m; i++) {
        hs = ( ( hs * p ) + s[i] );
        ht = ( ( ht * p ) + t[i] );
    }
    
    /* Searching */
    
    for (i=m; i <= n; i++) {
        if (ht == hs && memcmp(&t[ i-m ], s, m) == 0)
            positions.push_back(i - m);
        ht = rehash(t[i-m], t[i], ht, d);
    }
    return positions;
}
