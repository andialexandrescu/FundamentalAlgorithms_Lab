#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("graf.in");

int n, m;

void BFS(int start, vector<vector<int>> l_adiac, vector<int>& viz)
{
    viz[start] = 1;
    queue<int> q;
    q.push(start);
    while(q.size()!=0)
    {
        int i = q.front();// vrem muchia ij
        q.pop();
        cout<<i<<" ";
        for(int j: l_adiac[i])// parcurg si inserez vecinii
        {
            if(viz[j] == 0)
            {
                q.push(j);
                viz[j] = 1;
            }
        }
    }
}

int main() {
    int tip_orientare;
    fin>>n>>m>>tip_orientare;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane

    vector<int> viz; // vector pentru a marca nodurile vizitate
    viz.resize(n+1);// max pentru un graf cu o singura comp conexa

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        if(tip_orientare == 0)// graf neorientat
        {
            l_adiac[x].push_back(y);
            l_adiac[y].push_back(x);
        } else if(tip_orientare == 1)// graf orientat - lista reflecta muchiile care pleaca din x
        {
            l_adiac[x].push_back(y);
        }
    }
    for(int i = 0; i < n; i++)
    {
        cout<<i<<": ";
        for(int j : l_adiac[i])
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    //BFS(1, l_adiac, viz);

    int num_componente_conexe = 0;
    for (int i = 1; i <= n; i++) // parcurgem toate nodurile pentru a gasi componentele conexe
    {
        if(viz[i] == 0)
        {
            BFS(i, l_adiac, viz); // explorare noua comp conexa
            num_componente_conexe++;
        }
    }
    cout<<"Numarul de componente conexe: "<<num_componente_conexe<<endl;

    fin.close();
    return 0;
}
