#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

void printMatrix(vector <vector <int>> input)
{
    for (int j=0; j<input[0].size(); j++)
    {
        for (int i=0; i<input.size(); i++)
        {
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
}

int LCSubStr(string s, string t, int n, int m)
{
   
    // Create DP table
    int dp[2][m + 1];
    int res = 0;
       
      dp[0][0] = 0;
      dp[1][0] = 0;
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1;
                if (dp[i % 2][j] > res)
                    res = dp[i % 2][j];
            }
            else
                dp[i % 2][j] = 0;
        }
    }
    return res;
}


// Obtiene el substring común más largo - O(nm)
string llongestCommonSubstring(string s1, string s2)
{
    vector <vector <int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, 0)); // Crea una matriz de ceros para el dp - O(nm)

    printMatrix(dp);

    pair <int, int> max = {-1, -1}; // Longitud y posición por defecto para obttener la máxima substring
    for (int i=0; i<s2.size(); i++) // Itera por la segunda string - O(m)
    {
        for (int j=0; j<s1.size(); j++) // Itera por la primer string - O(n)
        {
            if (s1[i] == s2[j]) { // Si encouentra coincidencias asigna al dp de las coincidencias el valor de los dos chars anteriores - O(1)
                dp[i+1][j+1] = dp[i][j] + 1;
                if (dp[i+1][j+1] > max.first) max = {dp[i+1][j+1], i};
            }
        }
    }

    return to_string(max.second - max.first + 2) + " " + to_string(max.second + 1); // Regresa el resultado con formato - O(1)
}

void process()
{
    string s1 = "daxdnynytdnaxdnytnr";
    string s2 = "axdnytvab";

    cout << LCSubStr(s1, s2, s1.size(), );
}

#ifdef _WIN32
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    process();
}

#else

int main() 
{
    process();
}

#endif