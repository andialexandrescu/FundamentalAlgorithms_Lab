#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.in");

int main() {
    /*int n, m, tip_orientare;
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
    cout<<"Transformare in matrice de adiacenta:"<<endl;
    vector<vector<int>> matr_adiac(n+1, vector<int>(n+1));
    for(int i = 0; i < n; i++)
    {
        for(int j : l_adiac[i])
        {
            matr_adiac[i][j] = 1;
            if(tip_orientare == 0)// neorientat
            {
                matr_adiac[j][i] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<matr_adiac[i][j]<<" ";
        }
        cout<<endl;
    }*/
    int n, m, tip_orientare;
    fin>>n>>m>>tip_orientare;
    vector<vector<int>> matr_adiac;
    matr_adiac.resize(n+1, vector<int>(n+1));
    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        if(tip_orientare == 0)// graf neorientat
        {
            matr_adiac[x][y] = 1;
            matr_adiac[y][x] = 1;
        } else if(tip_orientare == 1)// graf orientat
        {
            matr_adiac[x][y] = 1;
        }
    }
    cout<<"Transformare in lista de adiacenta:"<<endl;
    vector<vector<int>> l_adiac(n+1);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(matr_adiac[i][j] == 1)
            {
                // nu mai conteaza tipul orientarii deoarece e reflectat deja in matrice
                l_adiac[i].push_back(j);
            }
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
