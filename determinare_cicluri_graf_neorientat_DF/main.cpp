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
bool ciclu_gasit = false;

void DFS(int x)
{
    viz[x] = 1;

    for(int y : l_adiac[x])
    {
        if(viz[y] == 0)
        {
            tata[y] = x;
            DFS(y);
        } else if(tata[x] != y) // (x, y) arc de intoarcere
        {
            cout<<"Arc de intoarcere: ("<<x<<", "<<y<<")"<<endl;
            stack<int> ciclu; // reconstruire ciclu
            ciclu.push(y); // se adauga y la ciclu
            int v = x;
            bool ciclu_valid = false;

            while(v != -1) // reconstruim traseul pana la nodul de inceput al ciclului
            {
                ciclu.push(v); // se adauga nodul curent la ciclu
                if (v == y)
                {
                    ciclu_valid = true;
                    break;
                }
                v = tata[v];
            }

            if(ciclu_valid == true)
            {
                cout<<"Ciclul gasit: ";
                while(!ciclu.empty())
                {
                    cout<<ciclu.top()<<" ";
                    ciclu.pop();
                }
                cout<<endl;
                ciclu_gasit = true;
            } else
            {
                cout<<"Nu s-a putut reconstrui ciclul deoarece am gasit un nod care apartine altui ciclu"<<endl;
            }
        }
    }
}

int main() {
    fin>>n>>m; // tip_orientare = 0

    l_adiac.resize(n + 1);
    viz.resize(n + 1, 0);
    tata.resize(n + 1, -1);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
        l_adiac[y].push_back(x);

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
        cout << "Nu s-au gasit cicluri in graf"<<endl;
    }

    fin.close();
    return 0;
}
/* Arc de intoarcere: (9, 1)
Ciclul gasit: 1 3 2 9 1
Arc de intoarcere: (8, 9)
Ciclul gasit: 9 4 8 9
Arc de intoarcere: (9, 8)
Nu s-a putut reconstrui ciclul deoarece am gasit un nod care apartine altui ciclu
Arc de intoarcere: (1, 9)
Nu s-a putut reconstrui ciclul deoarece am gasit un nod care apartine altui ciclu*/