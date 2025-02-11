#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("graf.in");

int n, m;

// explorare graf si determinare drum de la u la v
bool BFS(int start, int end, vector<vector<int>>& l_adiac, vector<int>& tata, vector<int>& viz)
{
    queue<int> q;
    q.push(start);
    viz[start] = 1;

    while(!q.empty())
    {
        int i = q.front();
        q.pop();

        for(int j : l_adiac[i])
        {
            if(viz[j] == 0)
            {
                q.push(j);
                viz[j] = 1;
                tata[j] = i; // parinte pentru reconstrucția drumului

                if (j == end) // daca ajungem la nodul final, returnam true
                {
                    return true;
                }
            }
        }
    }
    return false; // daca nu am gasit drumul pana la nodul final
}

// reconstructie drum de la u la v
void afiseaza_drumul(int start, int end, vector<int>& tata)
{
    stack<int> drum; // folosim o stiva pentru a inversa ordinea nodurilor din drum (deoarece drumul e construit de la end catre start)
    for(int v = end; v != -1; v = tata[v])
    {
        drum.push(v);
    }

    cout<<"Drumul de la "<<start<<" la "<<end<<": ";
    while(!drum.empty())
    {
        // afisez ce e in vf stivei si ii dau imediat pop din ea
        cout<<drum.top()<<" ";
        drum.pop();
    }
    cout << endl;
}

int main() {
    int tip_orientare;
    fin >> n >> m >> tip_orientare;

    vector<vector<int>> l_adiac(n + 1);
    vector<int> viz(n + 1, 0);
    vector<int> tata(n + 1, -1);

    int x, y;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y;
        if (tip_orientare == 0) // neorientat
        {
            l_adiac[x].push_back(y);
            l_adiac[y].push_back(x);
        } else if (tip_orientare == 1) // orientat
        {
            l_adiac[x].push_back(y);
        }
    }

    int u, v;
    cout<<"Introduceti nodurile u si v: ";
    cin>>u>>v;

    if(BFS(u, v, l_adiac, tata, viz))
    {
        afiseaza_drumul(u, v, tata);
    } else
    {
        cout<<"Nu exista un drum de la "<<u<<" la "<<v<<endl;
    }

    fin.close();
    return 0;
}
/* Introduceti nodurile u si v:0
9
 Drumul de la 0 la 9: 0 7 8 9*/