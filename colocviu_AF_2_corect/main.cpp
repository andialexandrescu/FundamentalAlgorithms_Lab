#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

const long long INF = numeric_limits<long long>::max();
long long n, m;

void floyd_warshall(vector<vector<long long>>& d, vector<vector<long long>>& p) {
    for (long long k = 1; k <= n; k++) { // intermediate node
        for (long long i = 1; i <= n; i++) { // source node
            for (long long j = 1; j <= n; j++) { // destination node
                if (d[i][k] != INF && d[k][j] != INF && d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = k; // update predecessor
                }
            }
        }
    }
}

bool is_intermediate_on_path(long long u, long long v, long long intermediar, const vector<vector<long long>>& d) {
    return (d[u][v] == d[u][intermediar] + d[intermediar][v]);
}

int main() {
    fin >> n >> m;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    vector<vector<long long>> p(n + 1, vector<long long>(n + 1, -1)); // predecessor matrix

    for (long long i = 1; i <= n; i++) {
        d[i][i] = 0; // distance from a node to itself is zero
    }

    for (long long i = 0; i < m; i++) {
        long long u, v, cost;
        fin >> u >> v >> cost;
        d[u][v] = min(d[u][v], cost); // handle multiple edges
        d[v][u] = min(d[v][u], cost); // bidirectional
        p[u][v] = v; // initialize predecessors
        p[v][u] = u;
    }

    floyd_warshall(d, p);

    long long question;
    fin >> question;
    for (long long i = 0; i < question; i++) {
        long long u, v, intermediar;
        fin >> u >> v >> intermediar;
        if (is_intermediate_on_path(u, v, intermediar, d)) {
            fout << "1";
        } else {
            fout << "0";
        }
    }

    return 0;
}
