#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");

int n, m;

bool bellman_held_karp(vector<vector<int>>& graf)
{
    vector<vector<bool>> dp(n + 1, vector<bool>(1 << n, false));
    dp[1][1] = true; // init dp[1][{1}] = true

    for(int mask = 1; mask < (1 << n); mask++) // toate submultimile de noduri
    {
        for(int i = 1; i <= n; i++)
        {
            if(mask & (1 << (i - 1))) // i e in submultimea mastii curente
            {
                for(int j = 1; j <= n; j++) // vecinii lui i
                {
                    if(graf[i][j] && (mask & (1 << (j - 1))) && dp[j][mask ^ (1 << (i - 1))])
                    {
                        dp[i][mask] = true;
                    }
                }
            }
        }
    }

    for(int i = 2; i <= n; i++)
    {
        if(dp[i][(1 << n) - 1] && graf[i][1])
        {
            return true;
        }
    }

    return false;
}

int main() {
    fin>>n>>m;
    vector<vector<int>> graf(n + 1, vector<int>(n + 1, 0));

    for(int i = 0; i < m; i++)
    {
        int x, y;
        fin>>x>>y;
        graf[x][y] = 1;
        graf[y][x] = 1;
    }

    if(bellman_held_karp(graf))
    {
        cout<<"Exista un ciclu hamiltonian"<<endl;

    } else
    {
        cout<<"Nu exista ciclu hamiltonian";
    }

    return 0;
}
