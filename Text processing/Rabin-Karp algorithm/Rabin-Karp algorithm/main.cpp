//
//  main.cpp
//  Rabin-Karp algorithm
//
//  Created bt al1as on 21/02/17.
//  Coptright © 2017 al1as. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>

int d = 1;

inline int rehash(char a, char b, int h) {
    int result = ((( h - a * d ) << 1 ) + b) % INT_MAX; // hash mat be huge, so we keep it in [0..INT_MAX]
    return result;
}

void RabinKarpAlgorithm(const char *t, const char *s, size_t n, size_t m) { 
    /*
     Here all the multiplications bt 2 are made using shifts.
     So q = MAX integer available
     */
    int ht, hs;
    size_t i;
    /*
     Preprocessing
     computes d = 2^( m-1 ) with the left-shift operator
     If d > MAX_INT then its automatically will make %
     */
    for ( i = 1; i < m; i++ ) d = ( d << 1 );
    
    ht = hs = 0;
    for ( i = 0; i < m; i++) {
        hs = ( ( hs << 1 ) + s[i] ) % INT_MAX;
        ht = ( ( ht << 1 ) + t[i] ) % INT_MAX;
    }
    
    /* Searching */
    
    for ( i=m; i < n; i++ ) {
        if ( ht == hs && memcmp( &t[ i-m ], s, m ) == 0 )
            std::cout << ( i-m ) << " ";
        ht = rehash(t[i-m], t[i], ht);
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
