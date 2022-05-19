#include "bits/stdc++.h"
using namespace std;

int nodes, edges;
vector <vector<int> > v;


int main(){
    cout << "Enter the number of nodes : ";cin >> nodes;
    cout << "Enter the number of edges : ";cin >> edges;

    v.resize(nodes, vector<int>(nodes));

    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            (i == j)? v[i][j] = 0 : v[i][j] = INT_MAX;

    cout << "Enter the edges : \n";
    for (int i = 0; i < edges; i++){
        int j,k, wt; cin >> j >> k >> wt;
        v[j][k] = wt;
    }
    
    for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
            if (j == i)
                continue;
            for (int k = 0; k < nodes; k++){
                if (k == i || j == k)
                    continue;
                if (v[j][i] != INT_MAX  and v[i][k] != INT_MAX)
                    v[j][k] = min(v[j][i] + v[i][k], v[j][k]);
            }
        }
    }

    int destination, source;
    cout << "Enter the source : "; cin >> source;
    cout << "Enter the destination : "; cin >> destination;

    cout << "The cost is : " << v[source][destination] << "\n";


    return 0;
}

