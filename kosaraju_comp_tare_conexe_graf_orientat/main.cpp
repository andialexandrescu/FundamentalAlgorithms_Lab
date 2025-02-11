#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");

void DFS(int x, vector<vector<int>> &l_adiac, vector<bool> &viz, stack<int> &s) // pas 1: se introduc dupa o parcurgere DFS intr-o stiva fiecare varf finalizat
{ // se va obtine ordonarea descrescatoare a vf dupa timpul de finalizare
    viz[x] = 1;
    for(int y : l_adiac[x])
    {
        if(viz[y] == 0)
        {
            DFS(y, l_adiac, viz, s);
        }
    }
    s.push(x); // x e finalizat
}

// subprogramul asta difera de cel de mai sus numai prin faptul ca nu se va adauga nimic in stiva
void DFS_transpus(int x, vector<vector<int>> &l_adiac_transpus, vector<bool> &viz) // se parcurge graful transpus folosind dfs cu nodurile din stiva s in ordinea descrescatoare a timpilor de finalizare
{ // nodurile care nu au fost vizitate formeaza componente tare conexe
    viz[x] = 1;
    cout<<x<<" "; // afisare nodul din componenta tare conexa
    for(int y : l_adiac_transpus[x])
    {
        if(viz[y] == 0)
        {
            DFS_transpus(y, l_adiac_transpus, viz);
        }
    }
}

int main()
{
    int n, m;
    fin>>n>>m; // tip_orientare = 1

    vector<vector<int>> l_adiac(n + 1), l_adiac_transpus(n + 1);
    vector<bool> viz(n + 1, false);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin >> x >> y;
        l_adiac[x].push_back(y);
        l_adiac_transpus[y].push_back(x); // graf transpus => inversare directie
    }

    stack<int> s;

    for(int i = 1; i <= n; i++) // pasul 1: parcurgere DFS pe graful initial
    {
        if(viz[i] == 0)
        {
            DFS(i, l_adiac, viz, s);
        }
    }

    fill(viz.begin(), viz.end(), 0); // reinit viz pentru graful transpus

    while(!s.empty())// pasul 3: parcurgere DFS pe graful transpus
    {
        int nod = s.top();
        s.pop();

        if(viz[nod] == 0)
        {
            cout<<"Componenta tare conexa: ";
            DFS_transpus(nod, l_adiac_transpus, viz);
            cout<<endl; // linie nouă pentru fiecare componenta
        }
    }

    fin.close();
    return 0;
}
/* Componenta tare conexa: 10 12
Componenta tare conexa: 1 4 7
Componenta tare conexa: 11 2
Componenta tare conexa: 5 6 8 3 9 */