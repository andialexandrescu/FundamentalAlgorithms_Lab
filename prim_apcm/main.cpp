#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility> // pentru std::pair
#include <fstream>

using namespace std;

ifstream fin("graf.in");

const int INF = numeric_limits<int>::max();

struct Muchie {
    int v;
    int cost;
};

class Comparare {
public:
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

void prim(int n, int start, const vector<vector<Muchie>>& graf)
{
    vector<int> d(n + 1, INF); // costuri minime
    vector<int> tata(n + 1, 0);
    vector<bool> inArbore(n + 1, false); // verif daca un nod este in arbore

    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparare> q;

    d[start] = 0;
    tata[start] = -1;

    q.push({start, d[start]}); // adaugare nod start in coada

    while (!q.empty())
    {
        int u = q.top().first; // nod cu costul minim
        q.pop();

        if(inArbore[u])
        {
            continue; // daca u este deja in arbore, nu e luat in considerare
        }

        inArbore[u] = true; // adaugam u in arbore altfel

        if(tata[u] != -1) // nu e radacina
        {
            cout<<"Muchia: "<<tata[u]<<" - "<<u<<" cu costul: "<<d[u]<<endl;
        }

        for(const auto& muchie : graf[u])
        {
            int v = muchie.v;
            int cost = muchie.cost;

            if(!inArbore[v] && cost < d[v]) // daca v nu este in arbore si costul este mai mic
            {
                d[v] = cost;
                tata[v] = u;
                q.push({v, d[v]}); // actualizare coada de prioritati
            }
        }
    }
}

int main() {
    int n, m;
    fin>>n>>m;
    vector<vector<Muchie>> graf(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, cost;
        fin>>u>>v>>cost;
        graf[u].push_back({v, cost});
        graf[v].push_back({u, cost});
    }

    cout << "Introduceti nodul de start: ";
    int start;
    cin>>start;

    prim(n, start, graf);

    fin.close();
    return 0;
}
/* Introduceti nodul de start:1
 Muchia: 1 - 3 cu costul: 11
Muchia: 3 - 5 cu costul: 8
Muchia: 3 - 6 cu costul: 9
Muchia: 6 - 4 cu costul: 2
Muchia: 4 - 2 cu costul: 3*/