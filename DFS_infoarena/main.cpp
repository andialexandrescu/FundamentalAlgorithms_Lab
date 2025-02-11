#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

long int n, m;
vector<bool> viz;

void DFS(int x, vector<vector<int>> &l_adiac)
{
    viz[x] = true;
    for(int y: l_adiac[x])
    {
        if(!viz[y])
        {
            DFS(y, l_adiac);
        }
    }
}

int main() {
    int k = 0;
    fin>>n>>m;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
    viz.resize(n+1, false);// max pentru un graf cu o singura comp conexa
    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);
    }
    for(int i = 1; i <= n; i++)
    {
        if(!viz[i])
        {
            DFS(i, l_adiac);
            k++;
        }
    }
    fout<<k;
    fin.close();
    fout.close();
    return 0;
}
