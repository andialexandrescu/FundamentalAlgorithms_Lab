#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("graf.in");
// reprez(u) va fi cu compresie de cale

struct Muchie {
    int u, v, cost;
};

bool compara(Muchie a, Muchie b)
{
    return a.cost < b.cost;
}

vector<int> tata, h; // vector de parinti si inaltimi pentru Union/Find

void init(int n)
{
    for(int i = 1; i <= n; i++)
    {
        tata[i] = i; // fiecare nod este propriul sau parinte la inceput
        h[i] = 0; // inaltimea initiala a fiecarui arbore este 0
    }
}

int reprez(int u)
{
    if(tata[u] != u)
    {
        tata[u] = reprez(tata[u]); // compresie de cale
    }
    return tata[u];
}

void reuneste(int u, int v)
{
    int ru = reprez(u);
    int rv = reprez(v);

    if(ru != rv) // daca sunt in componente diferite
    {
        // reuniune ponderata (legam arborele mai mic la radacina arborelui mai mare)
        if (h[ru] < h[rv])
        {
            tata[ru] = rv; // arborele u devine fiu al arborelui v
        } else
        {
            tata[rv] = ru; // arborele v devine fiu al arborelui u
            if(h[ru] == h[rv])
            {
                h[ru]++; // daca au aceeasi inaltime, crestem inaltimea arborelui rezultat
            }
        }
    }
}

int main() {
    int n, m;
    fin>>n>>m;

    vector<Muchie> l_muchii(m);
    for (int i = 0; i < m; i++) {
        fin >> l_muchii[i].u >> l_muchii[i].v >> l_muchii[i].cost;
    }

    sort(l_muchii.begin(), l_muchii.end(), compara); // Sortam muchiile dupa cost

    tata.resize(n + 1);
    h.resize(n + 1, 0);
    init(n); // init structurile Union/Find

    vector<Muchie> l_muchii_apcm;
    int nr_muchii_selectate = 0;
    int cost_total_apcm = 0;

    for(auto muchie : l_muchii)
    {
        if(reprez(muchie.u) != reprez(muchie.v)) // daca cele doua capete sunt in componente diferite
        {
            l_muchii_apcm.push_back(muchie);
            reuneste(muchie.u, muchie.v); // unim cele doua componente
            cost_total_apcm += muchie.cost;
            nr_muchii_selectate++;

            if (nr_muchii_selectate == n - 1) // daca am selectat deja n-1 muchii, ne oprim
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
