#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("graf.in");

int n, m;
vector<int> viz;
vector<int> desc; // timpul de inceput al explorarii
vector<int> t_fin; // timpul de finalizare al explorarii
vector<int> culoare; // culorile nodurilor 0 - alb (neexplorat), 1 - gri (in curs de explorare), 2 - negru (finalizat)
int timp = 0; // contor pentru timp

void DFS(int x, vector<vector<int>> l_adiac)
{
    culoare[x] = 1;
    timp++;
    desc[x] = timp; // incepe explorarea vf x
    viz[x] = 1;
    cout<<"Incepem explorarea nodului "<<x<<" la timpul "<<desc[x]<<endl;
    //cout<<x<<" ";
    for(int y: l_adiac[x])
    {
        if(viz[y] == 0)// sau culoare[y] == 0
        {
            cout<<"Exploram vecinul "<<y<<" din nodul "<<x<<endl;
            DFS(y, l_adiac);
        }
    }
    culoare[x] = 2; // nodul x a fost complet explorat
    timp++;
    t_fin[x] = timp;
    cout<<"Finalizam explorarea nodului "<<x<<" la timpul "<<t_fin[x]<<endl;
}

int main()
{
    int tip_orientare;
    fin>>n>>m>>tip_orientare;
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
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
    desc.resize(n + 1);
    t_fin.resize(n + 1);
    culoare.resize(n + 1, 0); // alb
    //DFS(1, l_adiac);
    for(int i = 1; i <= n; i++)
    {
        if(culoare[i] == 0)
        {
            DFS(i, l_adiac);
        }
    }
    fin.close();
    return 0;
}