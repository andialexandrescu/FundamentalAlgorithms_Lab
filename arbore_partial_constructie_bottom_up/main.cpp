#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.in");
// stim ca avem un graf conex neorientat (sigur va contine un arbore partial) si pe baza lui se va construi un arbore partial prin adaugare de muchii
// arbore partial are toate nodurile iar multimea muchiilor lui e o submultime a muchiilor grafului dat

int find(vector<int>& parent, int i)
{
    if(parent[i] == -1)
    {
        return i;
    }
    return find(parent, parent[i]);
}

void my_union(vector<int>& parent, int x, int y)
{
    parent[x] = y;
}

int main() {
    int n, m;
    fin>>n>>m;
    vector<pair<int, int>> l_muchii; // lista de muchii

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_muchii.push_back({x, y}); // se adauga muchia la l_muchii
    }

    vector<pair<int, int>> arbore; // arborele partial care va rezulta
    vector<int> tata(n + 1, -1); // init tata cu -1

    for(auto muchie : l_muchii)
    {
        int src = muchie.first;
        int dest = muchie.second;

        int src_tata = find(tata, src);
        int dest_tata = find(tata, dest);

        // daca nu formeaza un ciclu, adica cat timp arborele nu va fi conex, adaugam muchia in arbore
        if (src_tata != dest_tata)
        {
            arbore.push_back({src, dest});
            my_union(tata, src_tata, dest_tata);
        }
    }

    if(arbore.size() != n - 1)
    {
        cout<<"Arborele nu este complet! Numarul de muchii: "<<arbore.size()<<endl;
    } else
    {
        cout<<"Arborele partial este:\n";
        for(auto muchie : arbore)
        {
            cout<<muchie.first<<" - "<<muchie.second<<endl;
        }
    }

    fin.close();
    return 0;
}
