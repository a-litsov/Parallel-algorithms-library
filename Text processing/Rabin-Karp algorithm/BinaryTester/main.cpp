//
//  main.cpp
//  BinaryTester
//
//  Created by al1as on 11/03/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <omp.h>
#include <cstdio>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

using namespace std;

std::vector<long> RabinKarpAlgorithm(std::string t, std::string s);

int main (int argc, char * argv[])
{
    int num_threads = 1;
    if (argc > 1)
        num_threads = atoi(argv[1]);
    
    ifstream infile("search.in", ios::binary|ios::in);
    ofstream outfile("search.out", ios::binary|ios::out);
    
    vector<long> positions;
    /* reading */
    string inputStrings[2]; // 0 item is pattern, 1 item is text
    size_t length;
    
    for (int i = 0; i < 2; i++) {
        infile.read((char *)&length, sizeof(size_t));
        char buffer[length];
        infile.read(buffer, length);
        inputStrings[i] = buffer;
    }
    
    /* executing */
    omp_set_num_threads(num_threads);
    
    double time = omp_get_wtime();
    positions = RabinKarpAlgorithm(inputStrings[1], inputStrings[0]);
    time = omp_get_wtime() - time;
    
    /* writing */
    outfile.write((char*)&time, sizeof(double));
    length = positions.size();
    outfile.write((char*)&length, sizeof(size_t));
    outfile.write((char*)&positions[0], positions.size() * sizeof(long));
    
    outfile.close();
    infile.close();
    return 0;
}

#define main main_lumos_
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
