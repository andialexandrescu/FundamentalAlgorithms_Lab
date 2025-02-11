#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

// bfs pentru a determina distantele minime de la un set de noduri de control la toate celelalte noduri dintr-un graf neorientat

int n, m;

void BFS(vector<vector<int>> &l_adiac, vector<int> &puncte_control, vector<int> &dist)
{
    vector<int> viz;
    viz.resize(n+1);// max pentru un graf cu o singura comp conexe
    queue<int> q;
    for(int p : puncte_control)
    {
        dist[p] = 0;// dist punct control e 0
        q.push(p);
    }
    while(q.size()!=0)
    {
        int i = q.front();// vrem muchia ij
        q.pop();
        //cout<<i<<" ";
        for(int j: l_adiac[i])// parcurg si inserez vecinii
        {
            if(dist[j] == INT_MAX)// vecin neviz
            {
                dist[j] = dist[i] + 1;
                q.push(j);
            }
        }
    }
}

int main()
{
    fin>>n>>m;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);
    }
    for(int i = 0; i < n; i++)
    {
        cout<<i<<": ";
        for(int j : l_adiac[i])
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    // citire puncte de control din fisier
    vector<int> puncte_control;
    while(fin >> x)
    {
        puncte_control.push_back(x);
    }
    vector<int> dist(n+1, INT_MAX);// toate nodurile vom presupune ca au distanta infinita
    for(int x: puncte_control)
    {
        BFS(l_adiac, puncte_control, dist);
    }
    for(int i = 1; i <= n; i++)
    {
        cout<<dist[i]<<" ";
    }
    cout<<endl;
    fin.close();
    return 0;
}
