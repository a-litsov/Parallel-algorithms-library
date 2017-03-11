//
//  main.cpp
//  BinaryViewer
//
//  Created by al1as on 11/03/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

int main () {
    /* reading from input file */
    ifstream infile("search.in");
    string inputStrings[2]; // 0 item is pattern, 1 item is text
    size_t length;
    
    for (int i = 0; i < 2; i++) {
        infile.read((char *)&length, sizeof(size_t));
        char buffer[length];
        infile.read(buffer, length);
        inputStrings[i] = buffer;
    }
    infile.close();
    
    /* reading from output file */
    ifstream outfile("search.out");
    double time;
    outfile.read((char*)&time, sizeof(double));
    outfile.read((char*)&length, sizeof(size_t));
    long positions[length];
    outfile.read((char*)positions, length * sizeof(long));
    outfile.close();
    
    /* writing in view.txt file what we read */
    ofstream viewfile("view.txt");
    viewfile << "Pattern string:\n" << inputStrings[0] << "\n";
    viewfile << "     -------------------------------------------    \n";
    viewfile << "Text string:\n" << inputStrings[1] << "\n\n";
    
    viewfile << "Time is: " << time << "\n";
    viewfile << "Occurences found:\n";
    for (int i = 0; i < length; i++) {
        viewfile << positions[i] << " ";
    }
    viewfile.close();
    
    return 0;
}
