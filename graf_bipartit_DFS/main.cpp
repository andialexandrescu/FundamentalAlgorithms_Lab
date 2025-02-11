#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("graf.in");

vector<int> v[100];
vector<int> color(100, -1);

bool dfs(int node, int nodeColor)
{
    color[node] = nodeColor;
    bool ok = true;
    for (int i = 0; i < v[node].size(); i++)
    {
        if (color[v[node][i]] == -1)
        {
            ok = ok && dfs(v[node][i], !nodeColor);
        }
        else if (color[v[node][i]] == nodeColor)
        {
            return false;
        }
    }
    return ok;
}

int main()
{
    int n, m;
    fin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        fin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    cout << dfs(1, 0);
}