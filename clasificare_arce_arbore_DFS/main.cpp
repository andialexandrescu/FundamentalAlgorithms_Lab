#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.in");
// doar pentru graf orientat

int n, m;
vector<int> culoare;
vector<int> desc;
int timp = 0;

void DFS(int u, vector<vector<int>>& l_adiac)
{
    timp = timp + 1;
    desc[u] = timp;
    culoare[u] = 1;

    for(int v : l_adiac[u])
    {
        if(culoare[v] == 0) // arc de avansare directa in arbore = (u, v) cu v fiu al lui u (v a fost descoperit din u) = v este nevizitat
        { // neexplorat
            cout<<"Arc de arbore: ("<<u<<", "<<v<<")"<<endl;
            DFS(v, l_adiac);
        } else if(culoare[v] == 1) // arc de intoarcere = (u, v) cu v stramos al lui u (si care nu este de arbore) = inchide un circuit cu arcele din arborele DF = desc[v] < desc[u] < fin[u] < fin[v]
        { // in curs de explorare
            cout<<"Arc de intoarcere: ("<<u<<", "<<v<<")"<<endl;
        } else if (culoare[v] == 2)
        { // nod complet explorat
            if(desc[u] < desc[v]) // arc de avansare (inainte) = (u, v) cu v descendent al lui u care nu este insa fiu al lui = desc[u] < desc[v] < fin[v] < fin[u] si v nu e fiu (tata[v] != u)
            {
                cout<<"Arc de avansare: ("<<u<<", "<<v<<")"<<endl;
            } else // arc de traversare = desc[v]< fin[v] < desc[u] < fin[u]
            {
                cout<<"Arc de traversare: ("<<u<<", "<<v<<")"<<endl;
            }
        }
    }
    timp = timp + 1;
    culoare[u] = 2;// complet explorat
}

int main() {
    fin>>n>>m; // tip orientare = 1

    vector<vector<int>> l_adiac(n + 1);
    culoare.resize(n + 1, 0);
    desc.resize(n + 1, 0);

    int x, y;
    for(int i = 0; i < m; i++)
    {
        fin>>x>>y;
        l_adiac[x].push_back(y);
    }

    for(int i = 1; i <= n; i++)
    {
        if(culoare[i] == 0)
        {
            DFS(i, l_adiac);
        }
    }

    fin.close();
    return 0;
}
/*Arc de arbore: (1, 3)
Arc de intoarcere: (3, 1)
Arc de arbore: (3, 2)
Arc de arbore: (2, 5)
Arc de arbore: (3, 6)
Arc de avansare: (1, 5)
Arc de arbore: (1, 9)
Arc de traversare: (9, 6)
Arc de arbore: (9, 7)
Arc de arbore: (7, 4)
Arc de intoarcere: (4, 9)
Arc de arbore: (4, 8)
Arc de avansare: (9, 8)
Arc de arbore: (10, 11)
Arc de traversare: (11, 8)*/
// ceva interesant de retinut: se va strica daca nu pun muchia (x, y) urmata de (x, z) daca y < z ((x, z) urmat de (x, y) produce probleme)
/* din curs: În cazul unui graf neorientat există doar două tipuri de muchii în raport cu pădurea DF:
-	muchii de arbore (de avansare directa)
-	muchii de întoarcere (către un ascendent)  (ascendentul nu poate sa fie tata si acesta e muchie acre inchide un ciclu)
*/