#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("bfs.in");
ofstream fout("bfs.out");

int n, m;

void BFS(int start, vector<vector<int>> l_adiac, vector<int> &dist)
{
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while(q.size()!=0)
    {
        int i = q.front();// vrem muchia ij
        q.pop();
        for(int j: l_adiac[i])// parcurg si inserez vecinii
        {
            if(dist[j] == -1)// vecin nevizitat
            {
                q.push(j);
                dist[j] = 1 + dist[i];
            }
        }
    }
}

int main() {
    int start;
    fin>>n>>m>>start;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
    vector<int> dist(n + 1, -1);
    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
    }
    BFS(start, l_adiac, dist);
    for(int i = 1; i <= n; i++)
    {
        fout<<dist[i]<<" ";
    }
    fin.close();
    fout.close();
    return 0;
}
