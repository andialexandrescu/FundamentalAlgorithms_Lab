#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

int distanta_editare(const string& s1, const string& s2) // dist de editare/ Levenshtein
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= m; j++)
        {
            if(i == 0)
            {
                dp[i][j] = j; // daca s1 este gol, trebuie sa inseram toate caracterele din s2
            } else if (j == 0)
            {
                dp[i][j] = i; // daca s2 este gol, trebuie sa stergem toate caracterele din s1
            } else if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1]; // nu facem nimic
            } else
            {
                dp[i][j] = min({dp[i - 1][j] + 1, // stergere
                                dp[i][j - 1] + 1, // inserare
                                dp[i - 1][j - 1] + 1 // substitutie
                               });
            }
        }
    }
    return dp[n][m];
}

void k_means(const vector<string>& cuvinte, int k) // alg k-Means utilizand distanta de editare
{
    int n = cuvinte.size();
    vector<string> centroizi(k);
    vector<int> asignare(n); // atribuirea clusterelor

    // init: alegem aleator k centroizi
    for(int i = 0; i < k; i++)
    {
        centroizi[i] = cuvinte[rand() % n];
    }

    bool schimbare = true;

    while(schimbare)
    {
        schimbare = false;

        for(int i = 0; i < n; i++) // pasul 2: atribuirea clusterelor
        {
            int index = -1;
            int min_dist = numeric_limits<int>::max();
            for(int j = 0; j < k; j++)
            {
                int d = distanta_editare(cuvinte[i], centroizi[j]);
                if(d < min_dist)
                {
                    min_dist = d;
                    index = j;
                }
            }
            if(asignare[i] != index)
            {
                asignare[i] = index;
                schimbare = true; // a fost o schimbare
            }
        }

        // pasul 3: recalcularea centroizilor
        for (int j = 0; j < k; j++)
        {
            vector<string> membrii_cluster;
            for(int i = 0; i < n; i++)
            {
                if(asignare[i] == j)
                {
                    membrii_cluster.push_back(cuvinte[i]);
                }
            }

            if(!membrii_cluster.empty())
            {
                // gasire cel mai reprezentativ cuvant din cluster
                string nou_centroid;
                int min_dist_suma = numeric_limits<int>::max();

                for(const auto& cuvant : membrii_cluster)
                {
                    int dist_suma = 0;
                    for(const auto& member : membrii_cluster)
                    {
                        dist_suma += distanta_editare(cuvant, member);
                    }
                    if(dist_suma < min_dist_suma)
                    {
                        min_dist_suma = dist_suma;
                        nou_centroid = cuvant;
                    }
                }
                centroizi[j] = nou_centroid; // actualizare centroid
            }
        }
    }

    for(int j = 0; j < k; j++)
    {
        cout<<"Cluster "<<j + 1<<": ";
        for(int i = 0; i < n; i++)
        {
            if(asignare[i] == j)
            {
                cout<<cuvinte[i]<<" ";
            }
        }
        cout<<endl;
    }
}

int main() {
    int k;
    cout<<"Introduceti numarul de clustere (k): ";
    cin>>k;

    vector<string> cuvinte = {"este", "partial", "apa", "arbore", "martian", "minim", "ana", "sinonim", "care", "case"}; // Exemplu de date

    k_means(cuvinte, k);

    return 0;
}

/* Introduceti numarul de clustere (k):3
 Cluster 1: este apa arbore ana care case
Cluster 2: minim sinonim
Cluster 3: partial martian*/