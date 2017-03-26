//
//  main.cpp
//  Demonstration
//
//  Created by al1as on 26/03/17.
//  Copyright © 2017 al1as. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <set>

using namespace std;

const int INF = 1000000000; // значение "бесконечность"

void PrimAlgorithm(int n, int** g) {
    // алгоритм
    vector<bool> used (n);
    vector<int> min_e (n, INF), sel_e (n, -1);
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
            cout << v << " " << sel_e[v] << endl;
        
        for (int to=0; to<n; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
                
            }
    }
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


int** generateConnectedGraph(int n) {
    // Инициализация
    int** g = new int*[n];
    for (int i = 0; i < n; i++) {
        g[i] = new int[n];
        for (int j = 0; j < n; j++)
            g[i][j] = INF;
    }
    map<int, set<int>> groupMap;
    
    srand(time(0));
    for (int i = 0; i < n*(n-1)/8; i++) {
        int start = rand() % n;
        int end = rand() % n;
        while (end == start)
            end = rand() % n;
        int sourceStart = INF, tmpStart = getStart(start, g, n);
        while (tmpStart != INF) {
            sourceStart = tmpStart;
            tmpStart = getStart(start, g, n);
        }
        if (sourceStart != INF) {
            auto search = groupMap.find(start);
            if (search != groupMap.end())
                cout << "Error\n";
            search->second.insert(start);
            search->second.insert(end);
        } else {
            set<int> newGroup;
            newGroup.insert(start);
            newGroup.insert(end);
            int tmpEnd = getEnd(end, g, n);
            if (tmpEnd != INF) {
                auto search = groupMap.find(start);
                if (search != groupMap.end())
                    cout << "Error\n";
                newGroup.insert(search->second.begin(), search->second.end());
                groupMap.erase(search->first);
                groupMap.insert(std::pair<int, set<int>>(start, newGroup));
            }
        }
    }
    
    return g;
}

int main(int argc, const char * argv[]) {
    int n = 9;
    int** g = new int*[n];
    for (int i = 0; i < n; i++) {
        g[i] = new int[n];
        for (int j = 0; j < n; j++)
            g[i][j] = INF;
    }
    g[0][1] = 4; g[0][7] = 8;
    g[1][2] = 8; g[1][7] = 11;
    g[2][3] = 7; g[2][5] = 4; g[2][8] = 2;
    g[3][4] = 9; g[3][5] = 14;
    g[4][5] = 10;
    g[5][6] = 2;
    g[6][7] = 1; g[6][8] = 6;
    g[7][8] = 7;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] != INF) {
                g[j][i] = g[i][j];
                g[i][j] = INF;
            }
    PrimAlgorithm(n, g);
    for (int i = 0; i < n; i++)
        delete[] g[i];
    delete[] g;
    return 0;
}
