#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("graf.in");

int n, m;

bool is_bipartite(int start, vector<vector<int>> l_adiac)
{
    vector<int> viz;
    vector<int> color(n + 1, -1);
    viz.resize(n+1);// max pentru un graf cu o singura comp conexa
    viz[start] = 1;
    color[start] = 0;
    queue<int> q;
    q.push(start);
    while(q.size()!=0)
    {
        int i = q.front();// vrem muchia ij
        q.pop();
        cout<<i<<" ";
        for(int j: l_adiac[i])// parcurg si inserez vecinii
        {
            /*if(viz[j] == 0)
            {
                q.push(j);
                viz[j] = 1;
            }*/// de la BFS
            if(color[j] == -1)// daca vecinul nu a fost colorat inca
            {
                color[j] = 1 - color[i];// se alterneaza culoarea
                q.push(j);
            } else if(color[j] == color[i])// daca au aceeasi culoare, graful nu e bipartit
            {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int tip_orientare;
    fin>>n>>m>>tip_orientare;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
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

    bool ok = true;
    for(int i = 1; i <= n; i++)// se verifica pentru fiecare componenta conexa
    {
        if(l_adiac[i].size() > 0 && is_bipartite(i, l_adiac) == false)
        {
            ok = false;
            break;
        }
    }

    if(ok)
    {
        cout<<"e bipartit"<<endl;
    } else
    {
        cout<<"nu e bipartit"<<endl;
    }
    fin.close();
    return 0;
}