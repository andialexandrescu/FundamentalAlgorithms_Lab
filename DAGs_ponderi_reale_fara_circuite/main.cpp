#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

int n, m;

struct Muchie {
    int v, cost; // v e vf destinatie
};

void sortare_topologica(vector<vector<Muchie>>& l_adiac, vector<int>& sortare)
{
    vector<int> grad_in(n + 1, 0); // gradul de intrare pentru fiecare nod
    queue<int> q; // coada in care vor fi toate nodurile cu gradul de intrare 0, inca e vida

    for(int u = 1; u <= n; u++)
    {
        for(auto& muchie : l_adiac[u])
        {
            grad_in[muchie.v]++; // calculez grad intrare pentru fiecare nod
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(grad_in[i] == 0) // toate nodurile cu gradul de intrare 0 se pun in coada
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int u = q.front(); // extragem nodul din coada
        q.pop();
        sortare.push_back(u); // adaugare nod la lista de sortare

        for(auto& muchie : l_adiac[u])// se reduce gradul de intrare al vecinilor
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

void drumuri_minime_dag(int s, vector<vector<Muchie>>& l_adiac)
{
    vector<int> d(n + 1, numeric_limits<int>::max()); // vector de distante
    // unde d[u] va indica dupa fiecare pas costul minim al unui drum de la vf de start la u descoperit pana la acel moment
    vector<int> tata(n + 1, 0);

    d[s] = 0; // dist sursei e 0

    vector<int> sortare; // lista pentru ordonarea topologica, deoarece pt DAGs e utila o ordonare a vf a.i. daca (u, v) e o muchie, u sa se afle inaintea lui v
    sortare_topologica(l_adiac, sortare);

    for(int u : sortare) // pentru fiecare vf u se relaxeaza arcele conform ordinii topologice, pentru a gasi drumuri noi catre acestia
    {
        //cout<<"Nodul u = "<<u<<":";
        for(const auto& muchie : l_adiac[u])
        {
            int v = muchie.v;
            int cost = muchie.cost;
            if(d[u] != numeric_limits<int>::max() && d[u] + cost < d[v]) // relaxare muchia (u, v)
            {
                d[v] = d[u] + cost; // actualizare distanta si tata
                tata[v] = u;
            }
        }
        /*cout<<"     d/tata: [ ";
        for(int i = 1; i <= n ; i++)
        {
            cout<<i<<":"<<(d[i] == numeric_limits<int>::max() ? "inf" : to_string(d[i]))<<"/"<<tata[i]<<" ";
        }
        cout<<"]"<<endl;*/
    }

    cout<<"Distante minime de la sursa "<<s<<":"<<endl;
    for(int i = 1; i <= n; i++)
    {
        cout<<"       Distanta pana la nodul "<<i<<" este: "<<(d[i] == numeric_limits<int>::max() ? "inf" : to_string(d[i]))<<endl;
        if(tata[i] != 0)
        {
            cout << "       Tata pentru nodul  " << i << ": " << tata[i] << endl;
        }
    }
}

int main()
{
    fin>>n>>m;
    vector<vector<Muchie>> l_adiac(n + 1);
    int x, y, cost;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y>>cost;
        l_adiac[x].push_back({y, cost});
    }

    int s;
    cout<<"Introduceti varful sursa: ";
    cin>>s;

    drumuri_minime_dag(s, l_adiac);

    fin.close();
    return 0;
}
/* Introduceti varful sursa:3
 Sortarea topologica: 1 3 6 5 4 2
Nodul u = 1:     d/tata: [ 1:inf/0 2:inf/0 3:0/0 4:inf/0 5:inf/0 6:inf/0 ]
Nodul u = 3:     d/tata: [ 1:inf/0 2:8/3 3:0/0 4:inf/0 5:4/3 6:inf/0 ]
Nodul u = 6:     d/tata: [ 1:inf/0 2:8/3 3:0/0 4:inf/0 5:4/3 6:inf/0 ]
Nodul u = 5:     d/tata: [ 1:inf/0 2:8/3 3:0/0 4:6/5 5:4/3 6:inf/0 ]
Nodul u = 4:     d/tata: [ 1:inf/0 2:7/4 3:0/0 4:6/5 5:4/3 6:inf/0 ]
Nodul u = 2:     d/tata: [ 1:inf/0 2:7/4 3:0/0 4:6/5 5:4/3 6:inf/0 ]
Distante minime de la sursa 3:
       Distanta pana la nodul 1 este: inf
       Distanta pana la nodul 2 este: 7
       Tata pentru nodul  2: 4
       Distanta pana la nodul 3 este: 0
       Distanta pana la nodul 4 este: 6
       Tata pentru nodul  4: 5
       Distanta pana la nodul 5 este: 4
       Tata pentru nodul  5: 3
       Distanta pana la nodul 6 este: inf */