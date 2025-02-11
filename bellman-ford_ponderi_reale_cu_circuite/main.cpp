#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

ifstream fin("graf.in");

int n, m;

struct Muchie {
    int u, v, cost;
};

void bellman_ford(int s, vector<Muchie>& muchii, vector<int>& d, vector<int>& tata)
{
    d[s] = 0; // distanta sursei este 0

    for(int k = 1; k < n; k++) // relaxare arce de n-1 ori
    {
        for(const auto& muchie : muchii)
        {
            int u = muchie.u;
            cout<<"Nodul u = "<<u<<":";
            int v = muchie.v;
            int cost = muchie.cost;

            if (d[u] != numeric_limits<int>::max() && d[u] + cost < d[v])
            {
                d[v] = d[u] + cost;
                tata[v] = u;
            }
            cout<<"     d/tata: [ ";
            for(int i = 1; i <= n ; i++)
            {
                cout<<i<<":"<<(d[i] == numeric_limits<int>::max() ? "inf" : to_string(d[i]))<<"/"<<tata[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    // detectarea unui circuit negativ
    for(const auto& muchie : muchii)
    {
        int u = muchie.u;
        int v = muchie.v;
        int cost = muchie.cost;

        if (d[u] != numeric_limits<int>::max() && d[u] + cost < d[v])
        {
            d[v] = d[u] + cost;
            tata[v] = u;
            cout<<"Exista un circuit negativ in graf, deci rezultatul final nu va fi corect"<<endl;
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
    vector<Muchie> l_muchii(m);

    for(int i = 0; i < m; i++)
    {
        int x, y, cost;
        fin>>x>>y>>cost;
        l_muchii[i] = {x, y, cost};
    }

    int s;
    cout<<"Introduceti varful sursa: ";
    cin>>s;

    vector<int> d(n + 1, numeric_limits<int>::max());
    vector<int> tata(n + 1, -1);

    bellman_ford(s, l_muchii, d, tata);

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
 Nodul u = 1:     d/tata: [ 1:0/-1 2:5/1 3:inf/-1 4:inf/-1 5:inf/-1 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:5/1 3:7/1 4:inf/-1 5:inf/-1 ]
Nodul u = 3:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:inf/-1 5:inf/-1 ]
Nodul u = 2:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:inf/-1 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:inf/-1 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 3:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 2:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 3:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 2:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 1:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 3:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 2:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Nodul u = 4:     d/tata: [ 1:0/-1 2:4/3 3:7/1 4:5/2 5:4/4 ]
Distanta minima de la 1 la 2: 4
Drumul minim de la sursa la 2: 1 3 2
Distanta minima de la 1 la 3: 7
Drumul minim de la sursa la 3: 1 3
Distanta minima de la 1 la 4: 5
Drumul minim de la sursa la 4: 1 3 2 4
Distanta minima de la 1 la 5: 4
Drumul minim de la sursa la 5: 1 3 2 4 5*/