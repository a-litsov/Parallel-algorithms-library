#include <omp.h>
#include <vector>
#include <iostream>

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
