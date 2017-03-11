//
//  main.cpp
//  Checker
//
//  Created by al1as on 11/03/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

enum verdict : unsigned char { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result
{
private:
    FILE * bur;
public:
    enum ext_cls : unsigned char { NO = 1, VERDICT, MESSAGE, TIME, MEMORY, RES_EOF };
    result (bool read = false) { if (read) bur = fopen ("result.txt", "r"); else { bur = fopen ("result.txt", "w"); } } // bur = stderr;
    ~result () { write_type(ext_cls::RES_EOF); fclose (bur); }
    void write_type (ext_cls t) { fwrite (&t, sizeof (t), 1, bur); }
    void write_verdict (verdict v) { write_type (ext_cls::VERDICT); fwrite (&v, sizeof (v), 1, bur); }
    void write_message (string str) { write_type (ext_cls::MESSAGE); int l = str.size (); fwrite (&l, sizeof (l), 1, bur); fwrite (&str[0], sizeof (str[0]), l, bur); }
    void write_time (long long x) { write_type (ext_cls::TIME); fwrite (&x, sizeof (x), 1, bur); }
    void write_memory (unsigned long long x) { write_type (ext_cls::MEMORY); fwrite (&x, sizeof (x), 1, bur); }
} checker_result;

int main(int argc, const char * argv[]) {
    
    /* reading from student result file */
    ifstream infile("search.out");
    double studentTime;
    size_t studentLength;
    infile.read((char*)&studentTime, sizeof(double));
    infile.read((char*)&studentLength, sizeof(size_t));
    long studentPositions[studentLength];
    infile.read((char*)studentPositions, studentLength * sizeof(long));
    infile.close();
    
    /* reading from system result file */
    infile = ifstream("answer.txt");
    double systemTime;
    size_t systemLength;
    infile.read((char*)&systemTime, sizeof(double));
    infile.read((char*)&systemLength, sizeof(size_t));
    long systemPositions[systemLength];
    infile.read((char*)systemPositions, systemLength * sizeof(long));
    infile.close();
    
    bool isCorrect = true;
    if (studentLength == systemLength) {
        for (size_t i = 0; i < studentLength; i++)
            if(studentPositions[i] != systemPositions[i]) {
                isCorrect = false;
                break;
            }
    } else {
        isCorrect = false;
    }
    
    if (isCorrect) {
        checker_result.write_message("AC. Positions are equal.");
        checker_result.write_verdict(verdict::AC);
    } else {
        checker_result.write_message("WA. Output is not correct");
        checker_result.write_verdict(verdict::WA);
    }
    checker_result.write_time(studentTime * 1e7);
    return 0;
}
