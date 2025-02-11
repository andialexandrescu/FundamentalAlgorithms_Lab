#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("graf.in");

struct Muchie {
    int u, v, cost;
};

bool compara(Muchie a, Muchie b)
{
    return a.cost < b.cost;
}

vector<int> r; // vector de reprezentanti/ culori

void initializare(int u)
{
    r[u] = u; // fiecare nod este propriul sau reprezentant
}


int reprez(int u)
{
    return r[u]; // reprezentantul nodului u
}

void reuneste(int u, int v, int n)
{
    int r1 = reprez(u); // reprezentantul componentei care contine u
    int r2 = reprez(v); // reprezentantul componentei care contine v

    for(int k = 1; k < r.size(); k++)
    {
        if(r[k] == r2)
        {
            r[k] = r1; // toate nodurile din componenta lui v primesc reprezentantul lui u
        }
    }
}

int main()
{
    int n, m;
    fin>>n>>m;
    vector<Muchie> l_muchii(m);
    for(int i = 0; i < m; i++)
    {
        fin>>l_muchii[i].u>>l_muchii[i].v>>l_muchii[i].cost;
    }

    sort(l_muchii.begin(), l_muchii.end(), compara); // sortare muchii dupa cost

    r.resize(n + 1); // init vector reprezentanti

    for (int v = 1; v <= n; v++)
    {
        initializare(v); // fiecare nod este propriul sau reprezentant la inceput
    }

    vector<Muchie> l_muchii_apcm;
    int nr_muchii_selectate = 0;
    int cost_total_apcm = 0;

    for(auto muchie : l_muchii)
    {
        if(reprez(muchie.u) != reprez(muchie.v)) // daca cele doua capete sunt in componente diferite
        {
            l_muchii_apcm.push_back(muchie);
            reuneste(muchie.u, muchie.v, n); // unire dintre componente
            cost_total_apcm += muchie.cost;
            nr_muchii_selectate++;

            if(nr_muchii_selectate == n - 1) // daca am selectat deja n-1 muchii, ne oprim
            {
                break;
            }
        }
    }

    cout<<"Costul total al arborelui de cost minim este: "<<cost_total_apcm<<endl;
    cout<<"Muchiile din arborele de cost minim sunt:"<<endl;
    for(auto muchie : l_muchii_apcm)
    {
        cout<<muchie.u<<" - "<<muchie.v<<" cu costul "<<muchie.cost<<endl;
    }

    fin.close();
    return 0;
}
/* Costul total al arborelui de cost minim este: 33
Muchiile din arborele de cost minim sunt:
4 - 6 cu costul 2
2 - 4 cu costul 3
3 - 5 cu costul 8
3 - 6 cu costul 9
1 - 3 cu costul 11*/