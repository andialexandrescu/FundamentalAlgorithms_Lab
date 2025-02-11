#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");
// critica = prin eliminarea ei creste numarul de comp conexe ale grafului

int n, m;
vector<int> viz, niv_min, nivel;
vector<pair<int, int>> muchii_critice;
int timp = 0;

void DFS(int i, vector<vector<int>>& l_adiac)
{
    /* o muchie (v, u) este critica daca nu e continuta intr-un ciclu
     * inchis de o muchie de intoarcere adica nu exista nicio muchie
     * de intoarcere cu o extremitate in u sau intr-un descendent al lui u
     * si cealalta extremitate in v sau intr-un ascendent al lui v
     * */
    viz[i] = 1;
    timp = timp + 1;
    nivel[i] = niv_min[i] = timp;

    for(int j : l_adiac[i])// j vecin al lui i
    {
        if(viz[j]==0)// nod neviz, adica e muchie de avansare
        {
            nivel[j] = nivel[i] + 1;
            DFS(j, l_adiac);
            // formula B
            niv_min[i] = min(niv_min[i], niv_min[j]);// timpul cel mai mic de descoperire

            if(niv_min[j] > nivel[i])// conditie muchie critica
            {
                muchii_critice.push_back({i, j});
            }
        } else
        {
            if(nivel[j]<nivel[i]-1)// muchie de intoarcere
            {
                niv_min[i] = min(niv_min[i], nivel[j]);
            }
        }
    }
}

int main() {
    fin>>n>>m; // in general graf neorientat
    vector<vector<int>> l_adiac;
    l_adiac.resize(n+1);// pt n noduri exista maxim n-1 vecini, dar nu se stie cati sunt exact de aceea nu se redimensioneaza lungimea unei coloane
    viz.resize(n+1);// max pentru un graf cu o singura comp conexa
    niv_min.resize(n + 1, numeric_limits<int>::max()); // initializare cu infinit
    nivel.resize(n + 1);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);
    }

    for(int i = 1; i <= n; i++)
    {
        if(viz[i]==0)
        {
            DFS(i, l_adiac);
        }
    }

    cout<<"Muchiile critice sunt: "<<endl;
    for(auto& muchie : muchii_critice)
    {
        cout<<muchie.first<<" - "<<muchie.second<<endl;
    }
    fin.close();
    return 0;
}
/* Muchiile critice sunt:
2 - 6
7 - 8 */
