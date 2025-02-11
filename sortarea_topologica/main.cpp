#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("graf.in");

int n, m;

void sortare_topologica(vector<vector<int>>& l_adiac)
{
    vector<int> grad_in(n + 1, 0); // gradul de intrare pentru fiecare nod
    vector<int> sortare; // lista pentru ordonarea topologica
    queue<int> q; // coada in care vor fi toate nodurile cu gradul de intrare 0, inca e vida

    for(int u = 1; u <= n; u++)
    {
        for(int v : l_adiac[u])
        {
            grad_in[v]++; // calculez grad intrare pentru fiecare nod
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

        for(int v : l_adiac[u])// se reduce gradul de intrare al vecinilor
        {
            grad_in[v]--;
            if (grad_in[v] == 0)
            {
                q.push(v);
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

int main() {
    fin>>n>>m;// tip_orientare = 1

    vector<vector<int>> l_adiac(n + 1);
    int x, y;

    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        l_adiac[x].push_back(y);
    }

    sortare_topologica(l_adiac);

    fin.close();
    return 0;
}
/* Sortarea topologica: 1 3 6 5 4 2*/