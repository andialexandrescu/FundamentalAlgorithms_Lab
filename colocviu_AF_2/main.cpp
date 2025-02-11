#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

ifstream fin("graf.in");

const int INF = numeric_limits<int>::max();

long long int n, m;

void floyd_warshall(vector<vector<long long int>>& d, vector<vector<long long int>>& p)
{
    for(long long int k = 1; k <= n; k++) // nod intermediar
    {
        for(long long int i = 1; i <= n; i++) // nod sursa
        {
            for(long long int j = 1; j <= n; j++) // nod destinatie
            {
                if(d[i][k] != INF && d[k][j] != INF && d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j]; // actualizare predecesor
                }
            }
        }
    }
}

void afiseaza_drumul(long long int u, long long int v, long long int intermediar, const vector<vector<long long int>>& p)
{
    bool gasit = false;
    if(p[u][v] == -1)
    {
        //cout<<"Nu exista drum intre "<<u<<" si "<<v<<endl;
        cout<<"0";
        //return;
    }
    vector<long long int> drum;
    for(long long int at = v; at != -1; at = p[u][at])
    {
        drum.push_back(at);
        if(at == u)
        {
            break;
        }
    }
    //reverse(drum.begin(), drum.end());
    //cout<<"Drumul de la "<<u<<" la "<<v<<": ";
    for(long long int i = 0; i < drum.size(); i++)
    {
        //cout<<drum[i]<<" ";
        if (drum[i] == intermediar) {
            gasit = true;
        }
    }
    if (gasit == true) {
        cout<<"1";
    } else {
        cout<<"0";
    }
    //cout<<endl;
}

int main()
{
    fin>>n>>m;
    vector<vector<long long int>> d(n + 1, vector<long long int>(n + 1, INF));
    vector<vector<long long int>> p(n + 1, vector<long long int>(n + 1, -1)); // matrice predecesori

    for(long long int i = 1; i <= n; i++)
    {
        d[i][i] = 0; // dist de la un nod la el insusi este 0
        p[i][i] = 0; // pred pe diagonala nu poate exista deci se pune 0
    }

    for(long long int i = 0; i < m; i++)
    {
        long long int u, v, cost;
        fin>>u>>v>>cost;
        d[u][v] = cost;
        d[v][u] = cost;
        p[u][v] = u;
        p[v][u] = v;
    }


    floyd_warshall(d, p);

    /*cout<<"Matricea distantelor minime:"<<endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if (d[i][j] == INF)
            {
                cout<<"inf"<<" ";
            } else
            {
                cout<<d[i][j]<<" ";
            }
        }
        cout<<endl;
    }

    cout<<"Matricea predecesorilor:"<<endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout<<p[i][j]<<" ";
        }
        cout<<endl;
    }*/

    // se vor citi perechile pentru care dorim sa aflam drumul minim
    long long int question;
    //cout<<"Introduceti numarul de perechi de noduri pentru care sa fie afisat drumul minim: ";
    fin>>question;
    for(long long int i = 0; i < question; i++)
    {
        long long int u, v, intermediar;
        //cout<<"Introduceti perechea de noduri (u, v): ";
        fin>>u>>v>>intermediar;
        afiseaza_drumul(u, v, intermediar, p);
    }

    return 0;
}
/* Matricea distantelor minime:
0 5 8 1
8 0 3 5
5 10 0 2
3 8 11 0
Matricea predecesorilor:
0 1 2 1
4 0 2 3
4 1 0 3
4 1 2 0
Introduceti numarul de perechi de noduri pentru care sa fie afisat drumul minim:1
 Introduceti perechea de noduri (u, v):
1 3
Drumul de la 1 la 3: 1 2 3 */