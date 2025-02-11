#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

const int INF = numeric_limits<int>::max();
// cuplaj = orice doua muchii sunt neadiacente (nu au un vf in comun)
// cuplaj maxim = cuplaj de cardinal maxim

int n, m;

bool BFS(int start, int final, vector<vector<int> > &capacitate, vector<int> &tata)
{
    vector<int> viz_bfs(n + m + 2, 0); // +2 pentru sursa si destinatie

    queue<int> q;
    q.push(start);
    viz_bfs[start] = 1;
    tata[start] = -1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v = 0; v <= n + m + 1; v++)
        {
            if(viz_bfs[v] == 0 && capacitate[u][v] > 0)
            {
                q.push(v);
                viz_bfs[v] = 1;
                tata[v] = u;

                if(final == v)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int edmonds_karp(int start, int final, vector<vector<int> > &capacitate)
{
    vector<int> tata(n+m+2);
    int total_flux = 0;

    while(BFS(start, final, capacitate, tata))
    {
        int flux_lant = INF;
        for(int v = final; v != start; v = tata[v])
        {
            flux_lant = min(flux_lant, capacitate[tata[v]][v]);
        }

        for(int v = final; v != start; v = tata[v])
        {
            capacitate[tata[v]][v] -= flux_lant;
            capacitate[v][tata[v]] += flux_lant;
        }

        total_flux += flux_lant;
    }
    return total_flux;
}

/*void dfs(vector<int>& viz_dfs, int x, vector<vector<int>>& capacitate, vector<pair<int, int>>& cuplaje_maxime) // DFS pentru a explora toate solutiile de cuplaj maxim
{
    viz_dfs[x] = 1;

    for (int y = n + 1; y <= n + m; y++) // verif toate posibilele perechi de cuplaje
    {
        if (capacitate[x][y] == 0 && viz_dfs[y] == 0) // daca fluxul pe muchie este 0, adica face parte din cuplajul maxim
        {
            cuplaje_maxime.push_back({x, y - n});
            dfs(viz_dfs, y, capacitate, cuplaje_maxime);
        }
    }
}*/ // nu merge

int main()
{
    fin>>n>>m;
    vector<vector<int> > capacitate(n + m + 2, vector<int>(n + m + 2, 0));

    // se conecteaza X la sursa si Y la destinatie
    for(int i = 1; i <= n; i++)
    {
        capacitate[0][i] = 1; // 0 este sursa
    }
    for(int i = n + 1; i <= n + m; i++)
    {
        capacitate[i][n + m + 1] = 1; // n+m+1 este destinatia
    }

    for(int i = 0; i < m; i++)
    {
        int x, y;
        fin>>x>>y;
        capacitate[x][y + n] = 1; // y+n pentru ca Y incepe de la n+1
    }

    int start = 0, final = n + m + 1;
    cout<<"Fluxul maxim este: "<<edmonds_karp(start, final, capacitate)<<endl;

    vector<pair<int, int>> cuplaj_maxim;
    for(int i = 1; i <= n; i++)
    {
        for(int j = n + 1; j <= n + m; j++)
        {
            if(capacitate[i][j] == 0 && capacitate[j][i] == 1) // daca fluxul este 0, atunci muchia este in cuplaj
            {
                cuplaj_maxim.push_back({i, j - n}); // j-n pentru ca Y incepe de la n+1
            }
        }
    }
    // se va gasi o singura solutie cuplaj_maxim, dar vream sa generam toate solutiile pentru care cuplajul e maxim

    cout<<"Cuplajul maxim este: ";
    for(auto p : cuplaj_maxim)
    {
        cout<<"("<<p.first<<", "<<p.second<<") ";
    }
    cout<<endl;

    fin.close();
    return 0;
}