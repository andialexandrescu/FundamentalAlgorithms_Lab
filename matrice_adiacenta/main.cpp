#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.in");

int main() {
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
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<matr_adiac[i][j]<<" ";
        }
        cout<<endl;
    }
    fin.close();
    return 0;
}
