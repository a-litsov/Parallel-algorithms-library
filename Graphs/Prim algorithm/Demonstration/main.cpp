//
//  main.cpp
//  Demonstration
//
//  Created by al1as on 26/03/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <set>
#include <list>
#include <omp.h>

using namespace std;

const int INF = 1000000000; // значение "бесконечность"

int PrimAlgorithm(int n, int** g) {
    int res = 0;
    vector<bool> used (n);
    vector<int> min_e (n, INF); // min_e[i] - вес наименьшего допустимого ребра из вершины i
    vector<int> sel_e (n, -1); // sel_e[i] - конец этого наименьшего ребра
    min_e[0] = 0;
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        if (min_e[v] == INF) {
            cout << "No MST!";
            exit(0);
        }
        
        used[v] = true;
        if (sel_e[v] != -1)
            res += g[v][sel_e[v]];
        
#pragma omp parallel for
        for (int to=0; to<n; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
                
            }
    }
    return res;
}

int getStart(int end, int** g, int n) {
    for (int i = 0; i < n; i++)
        if (g[i][end] != INF)
            return i;
    return INF;
}

int getEnd(int start, int** g, int n) {
    for (int i = 0; i < n; i++)
        if (g[start][i] != INF)
            return i;
    return INF;
}

int fillOneVertex(int &start, int &end, int** g, int n) {
    srand(uint(time(0)));
    start = rand() % n;
    end = rand() % n;
    while (end == start)
        end = rand() % n;
    while (g[start][end] != INF) {
        start = rand() % n;
        end = rand() % n;
        while (end == start)
            end = rand() % n;
    }
    return g[end][start] = g[start][end] = rand() % 200;
}

int** initializeGraphMatrix(int n) {
    int** g = new int*[n];
    for (int i = 0; i < n; i++) {
        g[i] = new int[n];
        for (int j = 0; j < n; j++)
            g[i][j] = INF;
    }
    return g;
}

// n >= 4
int** generateConnectedGraph(int n) {
    int** g = initializeGraphMatrix(n);
    
    set<set<int>*> groupSet;
    
    // Generates n*(n-1)/4 vertices, fills groups
    for (int i = 0; i < (n-1)*(n-2)/2 + 1; i++) {
        int start, end, value;
        value = fillOneVertex(start, end, g, n);
        set<int> *foundStart = 0, *foundEnd = 0;
        bool isStartFound = false, isEndFound = false;
        for (auto const& item: groupSet) {
            auto search = item->find(start);
            if (search != item->end()) {
                foundStart = item;
                isStartFound = true;
            }
            search = item->find(end);
            if (search != item->end()) {
                foundEnd = item;
                isEndFound = true;
            }
        }
        if (foundStart != 0 && foundEnd != 0) {
            foundStart->insert(foundEnd->begin(), foundEnd->end());
            groupSet.erase(foundEnd);
        } else {
            if (isStartFound) {
                foundStart->insert(end);
            } else {
                if (isEndFound) {
                    foundEnd->insert(start);
                } else {
                    set<int>* newSet = new set<int>();
                    newSet->insert(start);
                    newSet->insert(end);
                    groupSet.insert(newSet);
                }
            }
        }
    }
    
    // Makes connections between groups
    set<set<int>*>::iterator it;
    for (it = groupSet.begin(); it != groupSet.end(); it++) {
        set<set<int>*>::iterator next_it = next(it);
        if (next_it != groupSet.end()) {
            int start = *((*it)->begin());
            int end = *((*next_it)->begin());
            fillOneVertex(start, end, g, n);
        }
    }

    
    return g;
}

void showGraph(int** g, int n) {
    cout << "Graph is:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10);
            cout << g[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(int argc, const char * argv[]) {
    int n = 200;
    int** g = generateConnectedGraph(n);
    
    showGraph(g, n);
    
    int minWeight = PrimAlgorithm(n, g);
    cout << "Min weight is " << minWeight << "\n";
    for (int i = 0; i < n; i++)
        delete[] g[i];
    delete[] g;
    return 0;
}
