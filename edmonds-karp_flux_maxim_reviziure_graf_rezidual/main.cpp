#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

const int INF = numeric_limits<int>::max();

int n, m;

// capacitate retine capacitatile
bool BFS(int start, int final, vector<vector<int> > &capacitate, vector<int> &tata) // BFS pentru a gasi un lant nesaturat
{
    vector<int> viz(n + 1, 0);

    queue<int> q;
    q.push(start);
    viz[start] = 1;
    tata[start] = -1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        // cout<<u<<" ";

        for(int v = 1; v <= n; v++)
        {
            if(viz[v] == 0 && capacitate[u][v] > 0) // capacitate reziduala pozitiva
            {
                q.push(v);
                viz[v] = 1;
                tata[v] = u;

                if(final == v) // a fost gasit un drum de ameliorare
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
    vector<int> tata(n+1);
    int total_flux = 0;
    tata[start] = -1;

    while(BFS(start, final, capacitate, tata))
    {
        int flux_lant = INF;
        for (int v = final; v != start; v = tata[v])
        {
            flux_lant = min(flux_lant, capacitate[tata[v]][v]); // fluxul maxim pe acest lant (capacitatea minima reziduala)
        }

        for (int v = final; v != start; v = tata[v]) // actualizare fluxuri pe arcele din lant
        {
            capacitate[tata[v]][v] -= flux_lant; // se reduce capacitatea reziduala
            capacitate[v][tata[v]] += flux_lant; // adaugare arc invers
        }

        total_flux += flux_lant;
    }
    return total_flux;
}

int main()
{
    fin>>n>>m;
    vector<vector<int> > capacitate(n + 1, vector<int>(n + 1, 0));

    for(int i = 0; i < m; i++)
    {
        int x, y, cap;
        fin>>x>>y>>cap;
        capacitate[x][y] = cap; // se adauga capacitatea arcului
    }

    int start, final; // sursa si destinatia
    fin>>start>>final;

    cout<<"Fluxul maxim este: "<<edmonds_karp(start, final, capacitate)<<endl;

    cout<<"Matricea capacitatilor este:"<<endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout<<capacitate[i][j]<<" ";
        }
        cout<<endl;
    }
    fin.close();
    return 0;
}

/*
10
0 0 0 0 4 0
0 0 5 0 0 2
6 0 0 2 0 0
0 0 1 0 4 0
4 0 0 0 0 0
0 5 0 5 0 0

*/