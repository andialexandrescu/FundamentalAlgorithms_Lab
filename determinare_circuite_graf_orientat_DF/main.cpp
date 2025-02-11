#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");

int n, m;
vector<int> viz;
vector<int> tata;
vector<vector<int>> l_adiac;
vector<int> t_fin;
int timp = 0;
bool ciclu_gasit = false;

void DFS(int x)
{
    viz[x] = 1;
    timp++;

    for (int y : l_adiac[x]) {
        if (viz[y] == 0)
        {
            tata[y] = x;
            DFS(y);
        } else if (t_fin[y] == 0) // y e gri, in explorare
        {
            cout<<"Arc de intoarcere: ("<<x<<", "<<y<<")"<<endl;

            stack<int> ciclu;
            int v = x;
            while(v != y)
            {
                ciclu.push(v);
                v = tata[v];
            }
            ciclu.push(y); // se adauga nodul de intoarcere
            ciclu.push(x); // inchid circuitul

            cout<<"Circuit gasit: ";
            while(!ciclu.empty())
            {
                cout<<ciclu.top()<<" ";
                ciclu.pop();
            }
            cout << endl;

            ciclu_gasit = true;
        }
    }

    timp = timp + 1;
    t_fin[x] = timp;
}

int main() {
    fin>>n>>m;

    l_adiac.resize(n + 1);
    viz.resize(n + 1, 0);
    tata.resize(n + 1, -1);
    t_fin.resize(n + 1, 0);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y); // graf orientat
    }

    for(int i = 1; i <= n; i++)
    {
        if(viz[i] == 0)
        {
            DFS(i);
        }
    }

    if(!ciclu_gasit)
    {
        cout<<"Nu s-au gasit circuite in graf"<<endl;
    }

    fin.close();
    return 0;
}