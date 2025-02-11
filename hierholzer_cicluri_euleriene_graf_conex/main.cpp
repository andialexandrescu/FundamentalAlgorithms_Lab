#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");

int n, m;

void hierholzer(vector<vector<int>>& l_adiac, int start)
{
    stack<int> s; // stiva pentru a retine lantul gasit (care de fapt e ciclu)
    vector<int> ciclu;
    vector<int> grad(n + 1, 0);

    s.push(start);

    for(int i = 1; i <= n; i++)
    {
        grad[i] = l_adiac[i].size(); // gradul fiecarui nod
    }

    while(!s.empty())
    {
        int v = s.top();
        if(grad[v] > 0)
        {
            for(int i = 0; i < l_adiac[v].size(); i++) // se gaseste o muchie incidenta si se elimina
            {
                int w = l_adiac[v][i];
                if(w != -1) // elimin muchia (v, w)
                {
                    l_adiac[v][i] = -1; // folosita
                    for(int j = 0; j < l_adiac[w].size(); j++)
                    {
                        if(l_adiac[w][j] == v)
                        {
                            l_adiac[w][j] = -1; // indexul lui w in l_adiac[w] e folosit
                            break;
                        }
                    }
                    grad[v]--;
                    grad[w]--;
                    s.push(w);
                    break;
                }
            }
        } else
        {
            // se adauag in ciclu si se scoate de pe stiva
            ciclu.push_back(v);
            s.pop();
        }
    }

    for(int i = ciclu.size() - 1; i >= 0; --i)
    {
        cout<<ciclu[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    fin>>n>>m;
    vector<vector<int>> l_adiac(n + 1);

    for(int j = 0; j < m; j++)
    {
        int x, y;
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);
    }

    hierholzer(l_adiac, 1);

    fin.close();
    return 0;
}
/* 1 2 3 4 2 5 6 7 5 4 1 */