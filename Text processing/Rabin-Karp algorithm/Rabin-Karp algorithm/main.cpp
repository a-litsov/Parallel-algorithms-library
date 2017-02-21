//
//  main.cpp
//  Rabin-Karp algorithm
//
//  Created by al1as on 21/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>

long long d = 1;

inline long long rehash(char a, char b, long long h) {
    long long result = (( h - a * d ) << 1 ) + b;
    return result;
}

void RabinKarpAlgorithm(const char *t, const char *s, size_t n, size_t m) {
    /*
     Here all the module multiplications by 2 are made using shifts.
     So q = max integer available
     */
    long long hy, hx;
    size_t i;
    /*
     Preprocessing
     computes d = 2^( m-1 ) with the left-shift operator
     */
    for ( i = 1; i < m; i++ ) d = ( d << 1 );
    
    hy = hx = 0;
    for ( i = 0; i < m; i++) {
        hx = ( ( hx << 1 ) + s[i] );
        hy = ( ( hy << 1 ) + t[i] );
    }
    
    /* Searching */
    
    for ( i=m; i < n; i++ ) {
        if ( hy == hx && memcmp( &t[ i-m ], s, m ) == 0 )
            std::cout << ( i-m ) << " ";
        hy = rehash(t[i-m], t[i], hy);
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::string s, t;
    std::cout << "Enter string T:";
    std::cin >> t;
    std::cout << "Enter string S:";
    std::cin >> s;
    std::cout << "Rabin-Karp algorithm results:\n";
    RabinKarpAlgorithm(t.c_str(), s.c_str(), t.size()+1, s.size());
    return 0;
}
