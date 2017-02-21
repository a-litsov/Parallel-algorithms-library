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

void RabinKarpAlgorithm(std::string s, std::string t) {
    // считаем все степени p
    const int p = 31;
    size_t size = t.length();
    long long p_pow [size];
    p_pow[0] = 1;
    for (size_t i=1; i<size; ++i)
        p_pow[i] = p_pow[i-1] * p;
    
    // считаем хэши от всех префиксов строки T
    long long h [size];
    for (size_t i=0; i<t.length(); ++i)
    {
        h[i] = (t[i] - 'a' + 1) * p_pow[i];
        if (i)  h[i] += h[i-1];
    }
    
    // считаем хэш от строки S
    long long h_s = 0;
    for (size_t i=0; i<s.length(); ++i)
        h_s += (s[i] - 'a' + 1) * p_pow[i];
    
    // перебираем все подстроки T длины |S| и сравниваем их
    for (size_t i = 0; i + s.length() - 1 < t.length(); ++i)
    {
        long long cur_h = h[i+s.length()-1];
        if (i)  cur_h -= h[i-1];
        // приводим хэши к одной степени и сравниваем
        if (cur_h == h_s * p_pow[i])
            std::cout << i << ' ';
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
    RabinKarpAlgorithm(s, t);
    return 0;
}
