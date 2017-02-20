//
//  main.cpp
//  Lagrange interpolation
//
//  Created by al1as on 20/02/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <string>

double getBasicPolynomialValue(int n, int polynomialNumber, double* x, double* y, double argument) {
    double upValue = 0, downValue = 0;
    for(int i = 0; i < n; i++)
        if(i != polynomialNumber) {
            upValue *= (argument - x[i]);
            downValue *= (x[polynomialNumber]-x[i]);
        }
    return upValue / downValue;
}

double getLagrangePolynomialValue(int n, double* x, double* y, double argument) {
    double result = 0;
#pragma omp parallel reduction (+:result)
    for(int i = 0; i < n; i++) {
        result += getBasicPolynomialValue(n, i, x, y, argument);
    }
    return result;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, const char * argv[]) {
    int threadsCount = 1;
    std::cout << "Enter threads number:";
    std::cin >> threadsCount;
    int pointsCount;
    std::string status;
    std::cout << "Enter own points?(y/n):";
    std::cin >>status;
    
    std::cout << "Enter points count:";
    std::cin >> pointsCount;
    double* x = new double[pointsCount];
    double* y = new double[pointsCount];
    
    if(status == "y") {
        std::cout << "Enter points:\n";
        for(int i = 0; i < pointsCount; i++) {
            std::cout << "x=";
            std::cin >> x[i];
            std::cout << "y=";
            std::cin >> y[i];
        }
    } else if(status == "n") {
        for(int i = 0; i < pointsCount; i++) {
            x[i] = fRand(0, 100000);
            y[i] = fRand(0, 100000);
        }
    }
    status = "y";
    double argument, start, end, value;
    while(status != "n") {
        std::cout << "Enter argument x=";
        std::cin >> argument;
        omp_set_num_threads(1);
        start = omp_get_wtime();
        value = getLagrangePolynomialValue(pointsCount, x, y, argument);
        end = omp_get_wtime();
        std::cout << "\nLagrange polynomial value at x=" << argument << " is " << value;
        std::cout << "\nTime with 1 thread is " << end - start;
        
        omp_set_num_threads(threadsCount);
        start = omp_get_wtime();
        value = getLagrangePolynomialValue(pointsCount, x, y, argument);
        end = omp_get_wtime();
        std::cout << "\nLagrange polynomial value at x=" << argument << " is " << value;
        std::cout << "\nTime with " << threadsCount << " thread is " << end - start;
        
        std::cout << "\nCalculate one more value?(y/n)";
        std::cin >> status;
    }
    return 0;
}
