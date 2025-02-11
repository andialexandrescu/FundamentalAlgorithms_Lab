#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

ifstream fin("graf.in");

const int MAX_COLORS = 6;

int n, m;

void colorare(vector<vector<int>>& l_adiac, vector<int>& culori, int nod)
{
    if(nod == n + 1)
    {
        for(int i = 0; i < n; i++) // colorare valida
        {
            for(int j : l_adiac[i])
            {
                if(culori[i] == culori[j])
                {
                    return;
                }
            }
        }

        for(int i = 1; i <= n; i++)
        {
            cout<<"Nod "<<i<<": Culoare "<<culori[i]<<endl;
        }
        exit(0); // solutie valida, se iese
    }

    for(int c = 1; c <= MAX_COLORS; ++c) // se incearca toate culorile pentru nodul curent
    {
        bool valid = true;
        for(int j : l_adiac[nod])
        {
            if(culori[j] == c)
            {
                valid = false;
                break;
            }
        }
        if(valid == true)
        {
            culori[nod] = c;
            colorare(l_adiac, culori, nod + 1); // recursiv se coloreaza urm nod
            culori[nod] = 0; // backtracking, se reseteaza culoarea
        }
    }
}

int main()
{
    fin>>n>>m;

    vector<vector<int>> l_adiac(n + 1);
    vector<int> culori(n + 1, 0);

    for(int j = 0; j < m; j++)
    {
        int x, y;
        fin>>x>>y;
        l_adiac[x].push_back(y);
        //l_adiac[y].push_back(x); // nu merge
    }

    colorare(l_adiac, culori, 1);

    return 0;
}
