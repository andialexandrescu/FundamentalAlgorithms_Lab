#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");

int n, m;
vector<int> viz;
vector<vector<int>> l_adiac;
stack<int> s; // stack

void DFS(int x)
{
    viz[x] = 1;
    for(int y : l_adiac[x])
    {
        if(viz[y] == 0)
        {
            DFS(y);
        }
    }
    s.push(x); // se adauga nodul x in stiva dupa ce toti vecinii au fost explorati
}

void sortare_topologica()
{
    for(int i = 1; i <= n; i++)
    {
        if(viz[i] == 0)
        {
            DFS(i);
        }
    }

    cout<<"Sortarea topologica: ";
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
}

int main() {
    fin>>n>>m; // tip_orientare = 1

    l_adiac.resize(n + 1);
    viz.resize(n + 1, 0);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
    }

    sortare_topologica();

    fin.close();
    return 0;
}
// stack holds nodes in reverse topological order (because nodes are pushed onto the stack after their descendants are fully explored), this means that when you pop the stack, you get the nodes in correct topological order