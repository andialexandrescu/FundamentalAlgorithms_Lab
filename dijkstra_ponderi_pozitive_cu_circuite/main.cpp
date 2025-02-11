#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

int n, m;

struct Muchie {
    int v, cost;
};

void dijkstra(int s, vector<vector<Muchie>>& l_adiac, vector<int>& d, vector<int>& tata)
{
    d[s] = 0; // distanta sursei este 0

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priority_q; // coada de prioritati pentru a gestiona nodurile
    priority_q.push({0, s}); // adaugare sursa in coada

    while(!priority_q.empty())
    {
        int u = priority_q.top().second; // se extrage nodul cu distanta minima din queue
        int dist_u = priority_q.top().first; // distanta minima
        priority_q.pop();
        cout<<"Nodul u = "<<u<<":";

        if(dist_u > d[u]) // nu se actualizeaza distanta
        {
            continue;
        }

        for(const auto& muchie : l_adiac[u])
        {
            int v = muchie.v;
            int cost = muchie.cost;

            if (d[u] + cost < d[v]) // relaxare muchie (u, v)
            {
                d[v] = d[u] + cost;
                tata[v] = u;
                priority_q.push({d[v], v}); // se adauga noua distanta in coada
            }
            cout<<"     d/tata: [ ";
            for(int i = 1; i <= n ; i++)
            {
                cout<<i<<":"<<(d[i] == numeric_limits<int>::max() ? "inf" : to_string(d[i]))<<"/"<<tata[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
}

void afiseaza_drum(int t, const vector<int>& tata)
{
    if(tata[t] == -1)
    {
        cout<<"Nu exista drum de la sursa la nodul "<<t<<endl;
        return;
    }

    vector<int> drum;
    for(int v = t; v != -1; v = tata[v])
    {
        drum.push_back(v);
    }

    cout<<"Drumul minim de la sursa la "<<t<<": ";
    for(int i = drum.size() - 1; i >= 0; i--)
    {
        cout<<drum[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    fin>>n>>m;

    vector<vector<Muchie>> l_adiac(n + 1);

    for(int i = 0; i < m; i++)
    {
        int x, y, cost;
        fin>>x>>y>>cost;
        l_adiac[x].push_back({y, cost});
    }

    int s;
    cout<<"Introduceti varful sursa: ";
    cin>>s;

    vector<int> d(n + 1, numeric_limits<int>::max());
    vector<int> tata(n + 1, -1);
    dijkstra(s, l_adiac, d, tata);

    for(int t = 1; t <= n; t++)
    {
        if(t != s)
        {
            cout<<"Distanta minima de la "<<s<<" la "<<t<< ": "<<(d[t] == numeric_limits<int>::max() ? "inf" : to_string(d[t]))<<endl;
            afiseaza_drum(t, tata);
        }
    }

    fin.close();
    return 0;
}
/* Introduceti varful sursa:1
 Nodul u = 1:     d/tata: [ 1:0/-1 2:15/1 3:inf/-1 4:inf/-1 5:inf/-1 6:inf/-1 ]
     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:inf/-1 5:inf/-1 6:inf/-1 ]
Nodul u = 3:     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:inf/-1 5:19/3 6:inf/-1 ]
     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:inf/-1 5:19/3 6:20/3 ]
Nodul u = 2:     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:20/3 ]
     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
Nodul u = 6:     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
Nodul u = 5:     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
     d/tata: [ 1:0/-1 2:15/1 3:11/1 4:18/2 5:19/3 6:17/2 ]
Nodul u = 6:Distanta minima de la 1 la 2: 15
Drumul minim de la sursa la 2: 1 2
Distanta minima de la 1 la 3: 11
Drumul minim de la sursa la 3: 1 3
Distanta minima de la 1 la 4: 18
Drumul minim de la sursa la 4: 1 2 4
Distanta minima de la 1 la 5: 19
Drumul minim de la sursa la 5: 1 3 5
Distanta minima de la 1 la 6: 17
Drumul minim de la sursa la 6: 1 2 6 */