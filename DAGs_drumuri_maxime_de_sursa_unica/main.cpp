#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

int n, m; // n = nr de activitati, m = nr de dependente intre activitati

struct Muchie {
    int v, cost;
};

void sortare_topologica(vector<vector<Muchie>>& l_adiac, vector<int>& sortare)
{
    vector<int> grad_in(n + 1, 0); // gradul de intrare pentru fiecare nod
    queue<int> q; // coada pentru nodurile cu gradul de intrare 0

    for(int u = 1; u <= n; u++)
    {
        for(const auto& muchie : l_adiac[u])
        {
            grad_in[muchie.v]++;
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(grad_in[i] == 0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        sortare.push_back(u);

        for(const auto& muchie : l_adiac[u])
        {
            grad_in[muchie.v]--;
            if(grad_in[muchie.v] == 0)
            {
                q.push(muchie.v);
            }
        }
    }

    if(sortare.size() != n)
    {
        cout<<"Graful orientat are un circuit. Nu se poate face sortarea topologica"<<endl;
    } else
    {
        cout<<"Sortarea topologica: ";
        for(int i : sortare)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

void drumuri_maxime_dag(vector<vector<Muchie>>& l_adiac)
{
    vector<int> d(n + 1, numeric_limits<int>::min()); // vector de durate, va fi initializat cu -infinit
    vector<int> tata(n + 1, 0);
    d[7] = 0; // durata sursei este 0

    vector<int> sortare;
    sortare_topologica(l_adiac, sortare);

    for(int u : sortare)
    {
        for(const auto& muchie : l_adiac[u])
        {
            cout<<"Nodul u = "<<u<<":";
            int v = muchie.v;
            int cost = muchie.cost;
            if(d[u] != numeric_limits<int>::min() && d[u] + cost > d[v]) // relaxare muchie pentru drum maxim (se schimba directia inegalitaii)
            {
                d[v] = d[u] + cost;
                tata[v] = u;
            }
            cout<<"     d/tata: [ ";
            for(int i = 1; i <= n ; i++)
            {
                cout<<i<<":"<<(d[i] == numeric_limits<int>::min() ? "inf" : to_string(d[i]))<<"/"<<tata[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }

    cout<<"Durata minima de finalizare a proiectului:"<<(d[8] == -1000000000 ? "inf" : to_string(d[8]))<<endl;
}

int main()
{
    fin>>n>>m;
    vector<int> durate(n + 1); // durata fiecarei activitati
    vector<vector<Muchie>> l_adiac(n + 3); // +2 pentru nodul sursa si nodul destinatie care vor fi adaugate

    for(int i = 1; i <= n; i++)
    {
        fin>>durate[i]; // citim durata activitatii i
    }

    for(int i = 0; i < m; i++)
    {
        int x, y;
        fin>>x>>y; // se citesc perechile de activitati (activitate_i activitate_j)
        l_adiac[x].push_back({y, durate[x]}); // se adauga dependenta cu costul corespunzator
    }

    for (int i = 1; i <= n; i++) // conectare nod sursa care e (n+1)
    {
        bool bool_sursa = true;
        for(int j = 1; j <= n; j++)
        {
            for(const auto& muchie : l_adiac[j])
            {
                if(muchie.v == i) // daca exista o dependenta
                {
                    bool_sursa = false;
                    break;
                }
            }
            if(!bool_sursa)
            {
                break;
            }
        }
        if(bool_sursa)
        {
            l_adiac[n + 1].push_back({i, 0}); // adaugare arc din sursa catre activitate
            //m++;
        }
    }

    for(int i = 1; i <= n; i++) // conectare nod destinatie care e (n+2)
    {
        if(l_adiac[i].empty()) // daca activitatea nu are dependente
        {
            l_adiac[i].push_back({n + 2, durate[i]}); // adaugare arc din activitate catre destinatie
            //m++;
        }
    }

    n = n + 2;

    for(int i = 1; i <= n; i++)
    {
        cout<<i<<": ";
        for(const auto& muchie : l_adiac[i])
        {
            cout<<"("<<muchie.v<<", "<<muchie.cost<<") ";
        }
        cout << endl;
    }

    drumuri_maxime_dag(l_adiac);

    fin.close();
    return 0;
}
/* 1: (2, 7)
2: (3, 4) (6, 4)
3: (5, 30) (6, 30)
4: (3, 12)
5: (8, 2)
6: (8, 5)
7: (1, 0) (4, 0)
8:
Sortarea topologica: 7 1 4 2 3 5 6 8
Nodul u = 7:     d/tata: [ 1:0/7 2:inf/0 3:inf/0 4:inf/0 5:inf/0 6:inf/0 7:0/0 8:inf/0 ]
Nodul u = 7:     d/tata: [ 1:0/7 2:inf/0 3:inf/0 4:0/7 5:inf/0 6:inf/0 7:0/0 8:inf/0 ]
Nodul u = 1:     d/tata: [ 1:0/7 2:7/1 3:inf/0 4:0/7 5:inf/0 6:inf/0 7:0/0 8:inf/0 ]
Nodul u = 4:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:inf/0 6:inf/0 7:0/0 8:inf/0 ]
Nodul u = 2:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:inf/0 6:inf/0 7:0/0 8:inf/0 ]
Nodul u = 2:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:inf/0 6:11/2 7:0/0 8:inf/0 ]
Nodul u = 3:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:42/3 6:11/2 7:0/0 8:inf/0 ]
Nodul u = 3:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:42/3 6:42/3 7:0/0 8:inf/0 ]
Nodul u = 5:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:42/3 6:42/3 7:0/0 8:44/5 ]
Nodul u = 6:     d/tata: [ 1:0/7 2:7/1 3:12/4 4:0/7 5:42/3 6:42/3 7:0/0 8:47/6 ]
Durata minima de finalizare a proiectului:47*/
