#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility> // pentru std::pair

using namespace std;

ifstream fin("graf.in");

const int N = 100; // dimensiune labirint maxima
int labirint[N][N]; // 1 - perete, 0 - celula libera
bool vizitat[N][N];
int tata[N][N]; // matrice tati
int n, m; // dimensiunile labirintului

// direcțiile de miscare: nord, sud, est, vest
const int dx[] = {-1, 1, 0, 0};// nord, sud
const int dy[] = {0, 0, 1, -1};// est, vest

pair<bool, pair<int, int>> BFS(int startX, int startY)
{
    queue<pair<int, int>> q;
    q.push({startX, startY});
    vizitat[startX][startY] = true;
    tata[startX][startY] = -1;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if(x==0 || x==n-1 || y==0 || y==m-1) // marginea labirintului
        {
            //cout<<"Am gasit o iesire la: ("<<x<<", "<<y<<")"<<endl;
            return {true, {x, y}};  // am gasit o iesire
        }

        for (int i = 0; i < 4; i++)// parcurgem vecinii in toate directiile
        {
            int newX = x+dx[i];
            int newY = y+dy[i];

            // daca noua pozitie e valida (respect mariginile, sa nu fie deja vizitata pozitia si sa nu existe obstacol)
            if (newX>=0 && newX<n && newY>=0 && newY<m && !vizitat[newX][newY] && labirint[newX][newY]==0)
            {
                q.push({newX, newY});
                vizitat[newX][newY] = true;
                tata[newX][newY] = x*m+y; // tata e retinut in formatul linie * m + coloana
            }
        }
    }
    return {false, {-1, -1}}; // nu am gasit nicio iesire
}

// reconstruire drum de la start la iesirea gasita
void afiseaza_drumul(int startX, int startY, int exitX, int exitY)
{
    vector<pair<int, int>> drum;
    int x = exitX;
    int y = exitY;

    while(tata[x][y] != -1)
    {
        drum.push_back({x, y});
        int parent = tata[x][y];
        x = parent / m; // linia parintelui
        y = parent % m; // coloana parintelui
    }
    drum.push_back({startX, startY}); // adaugare pct start

    cout << "Drumul minim catre iesire: ";
    for(auto it = drum.rbegin(); it != drum.rend(); ++it) // afisare ordine inversa
    {
        cout<<"("<<it->first<<", "<<it->second<<") ";
    }
    cout<<endl;
}

int main()
{
    fin>>n>>m;// dim labirint
    for(int i = 0; i < n; i++) // matricea labirintului (0 - liber, 1 - perete)
    {
        for(int j = 0; j < m; j++)
        {
            fin>>labirint[i][j];
            // init
            vizitat[i][j] = false;
            tata[i][j] = -1;
        }
    }

    int startX, startY;
    cout<<"Introduceti coordonatele de start (x y): ";
    cin>>startX>>startY;

    if(labirint[startX][startY] == 1)
    {
        cout << "Celula de start este un perete. Nu se poate porni." << endl;
        return 0;
    }

    auto [foundExit, exitCoords] = BFS(startX, startY);

    if(foundExit)
    {
        afiseaza_drumul(startX, startY, exitCoords.first, exitCoords.second);
    } else
    {
        cout<<"Nu exista un drum catre iesire"<<endl;
    }

    return 0;
}
/* Introduceti coordonatele de start (x y):3 1
 Drumul minim catre iesire: (3, 1) (3, 2) (4, 2) (5, 2) */