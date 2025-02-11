#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.in");

int main() {
    int n, m, tip_orientare;
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
    fin.close();
    return 0;
}
