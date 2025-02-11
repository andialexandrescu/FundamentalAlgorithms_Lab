#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

ifstream fin("graf.in");

int n, m;
// punct critic = eliminarea duce la cresterea numarului de comp conexe
// radacina e pct crtic daca are cel putin 2 fii in arborele DF
// un alt vf i e critic daca are cel putin un fiu j cu niv_min[j]>=nivel[i]
vector<int> viz, niv_min, nivel, tata;
vector<int> puncte_critice;
int timp = 0;

void DFS(int i, vector<vector<int>>& l_adiac)
{
    viz[i] = 1;
    timp++;
    nivel[i] = niv_min[i] = timp;

    int copii = 0;
    for(int j : l_adiac[i])
    {
        if(viz[j] == 0)
        {
            copii++;
            tata[j] = i;
            nivel[j] = nivel[i] + 1;
            DFS(j, l_adiac);
            niv_min[i] = min(niv_min[i], niv_min[j]);

            if((tata[i] == -1 && copii > 1) || (tata[i] != -1 && niv_min[j] >= nivel[i]))// conditia pentru punct critic
            {
                puncte_critice.push_back(i);
            }
        } else if(j != tata[i]) // nod vizitat
        {
            niv_min[i] = min(niv_min[i], nivel[j]);
        }
    }
}

int main()
{
    fin>>n>>m; // tip_orientare = 0
    vector<vector<int>> l_adiac(n + 1);
    viz.resize(n + 1, 0);
    niv_min.resize(n + 1, numeric_limits<int>::max());
    nivel.resize(n + 1, 0);
    tata.resize(n + 1, -1);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);
    }

    for(int i = 1; i <= n; i++)
    {
        if(viz[i] == 0)
        {
            DFS(i, l_adiac);
        }
    }

    cout<<"Punctele critice sunt: "<<endl;
    for(int i : puncte_critice)
    {
        cout<<i<<endl;
    }

    fin.close();
    return 0;
}
/*
 *
 * 8 10
1 2
2 6
2 7
1 7
7 8
3 4
3 5
3 6
6 5
5 4
 Punctele critice sunt:
6
2
7*/