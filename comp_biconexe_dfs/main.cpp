#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

ifstream fin("graf.in");

int n, m;
// punct critic = eliminarea duce la cresterea numarului de comp conexe
// radacina e pct crtic daca are cel putin 2 fii in arborele DF
// un alt vf i e critic daca are cel putin un fiu j cu niv_min[j]>=nivel[i]
vector<int> viz, niv_min, nivel, tata;
vector<vector<pair<int, int>>> componente_biconexe; // vector de vectori de perechi
// comp biconexa  subgraf biconex maximal
stack<pair<int, int>> stiva;
int timp = 0;

void print_stack(const stack<pair<int, int>>& st)
{
    stack<pair<int, int>> copy = st;
    cout<<"Stiva: ";
    while(!copy.empty())
    {
        cout<<"("<<copy.top().first<<", "<<copy.top().second<<") ";
        copy.pop();
    }
    cout<<endl;
}

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
            stiva.push({i, j});
            //cout<<"Adaugat la stiva: ("<<i<<", "<<j<<")"<<endl;
            //print_stack(stiva);
            DFS(j, l_adiac);
            niv_min[i] = min(niv_min[i], niv_min[j]);

            if(niv_min[j] >= nivel[i]) // daca i e pct critic
            {
                vector<pair<int, int>> componenta;

                while(stiva.top() != make_pair(i, j))
                {
                    componenta.push_back(stiva.top());
                    //cout<<"Extragem din stiva: ("<<stiva.top().first<<", "<<stiva.top().second<<")"<<endl;
                    stiva.pop();
                }

                componenta.push_back(stiva.top());// adaugare muchie curenta (i, j)
                //cout<<"Extragem din stiva: ("<<stiva.top().first<<", "<<stiva.top().second<<")"<<endl;
                stiva.pop();

                componente_biconexe.push_back(componenta); // salvam componenta biconexa

                /*cout<<"Componenta biconexa gasita: ";
                for(const auto& muchie : componenta)
                {
                    cout<<"("<<muchie.first<<", "<<muchie.second<<") ";
                }
                cout<<endl;*/
            }
        } else if(j != tata[i] && nivel[j] < nivel[i]) // muchie de intoarcere
        {
            niv_min[i] = min(niv_min[i], nivel[j]);
            stiva.push({i, j});
            //cout<<"Adaugat muchie de intoarcere la stiva: ("<<i<<", "<<j<<")"<<endl;
            //print_stack(stiva);
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

    cout<<"Componentele biconexe sunt:"<<endl;
    for(const auto& componenta : componente_biconexe)
    {
        for(const auto& muchie : componenta)
        {
            cout<<muchie.first<<" - "<<muchie.second<<" ";
        }
        cout<<endl;
    }

    fin.close();
    return 0;
}
/* Componentele biconexe sunt:
5 - 6 5 - 3 4 - 5 3 - 4 6 - 3
2 - 6
7 - 8
7 - 1 2 - 7 1 - 2*/