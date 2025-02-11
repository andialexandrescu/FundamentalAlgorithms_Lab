#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("graf.in");
// echipele joaca conform unui program de prioritati <=> sortare topologica
// insa trebuie in cazul in care o echipa poate fi introdusa pe stiva (are grad 0) sa fie selectata mai intai cea in ordine lexico-grafica
// deoarece echipele cu numere mai mici apar cat mai devreme posibil

int n, m; // n echipe, m reguli
vector<int> viz;
vector<vector<int>> l_adiac;
vector<vector<int>> ordine;
stack<int> s; // stack
priority_queue<int, vector<int>, greater<int>> pq;

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

void sortare_topologica(vector<vector<int>> l_adiac)
{
    for(int i = 1; i <= n; i++)
    {
        if(viz[i] == 0)
        {
            DFS(i);
        } /*else {
            queue<int> q; // o reinitializez
            while(!s.empty()) {
                q.push(s.top());
                //cout<<s.top()<<" ";
                s.pop();
            }
            vector<int> top_q(q.size() , 0);
            for(int i = 0; i < q.size(); i++) {
                top_q[i] = q.front();
                q.pop();
            }
            ordine.push_back(top_q);
        }*/
    }
    while(!s.empty()) {
        cout<<s.top()<<" ";
        s.pop();
    }

    /*sort(ordine.begin(), ordine.end());
    for(int i = 0; i < ordine.size(); i++) {
        for(int j = 0; j < ordine[i].size(); j++) {
            cout << ordine[i][j] << " ";
        }
    }*/

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
    /*// as vrea sa sortez a.i. in lista de adiacenta sa fie retinute vecinii prima oara pentru perechi de forma x: y unde y nu are vecini
    sort(l_adiac.begin(), l_adiac.end(), compara);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l_adiac[i].size(); j++) {
            cout<<l_adiac[i][j]<<" ";
        }

    }*/


    sortare_topologica(l_adiac);
    /*while(!pq.empty()) {
        cout<<pq.top()<<" ";
        pq.pop();
    }*/

    fin.close();
    return 0;
}
// renunt
// stack holds nodes in reverse topological order (because nodes are pushed onto the stack after their descendants are fully explored), this means that when you pop the stack, you get the nodes in correct topological order