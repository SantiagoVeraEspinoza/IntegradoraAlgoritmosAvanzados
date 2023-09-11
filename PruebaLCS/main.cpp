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

// Encuentra el substring común más largo - O(nn2)
string longestCommonSubstring(const string &s1, const string &s2) {
    int n = s1.length();
    int m = s2.length();

    // Usar dos filas para el dp - O(n)
    vector<vector<int>> dp(2, vector<int>(m + 1, 0));

    int maxLength = 0; // Almacena la longitud de la subcadena más larga
    int endPosS1 = 0;  // Para almacenar el índice del carácter final en s1 de LCS

    // Llena la tabla
    for (int i = 1; i <= n; i++) { // Itera por ambas strings - O(nn2)
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) { // Si encuentra una string igual actualiza el dp
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1; // Usa la fila par o impar para escribir en el espacio j la repsuesta de los dos caracteres anteriores anterior más 1
                if (dp[i % 2][j] > maxLength) { // Si la respuesta es mayor al máximo valor actualiza los máximos valores
                    maxLength = dp[i % 2][j];
                    endPosS1 = i;
                }
            } else { // Sino, deja el valor como 0
                dp[i % 2][j] = 0;
            }
        }
    }

    // Si no hay subcadena común
    if (maxLength == 0)
        return "";

    // Devuelve la subcadena común más larga - O(1)
    return to_string(endPosS1 - maxLength + 1) + " " + to_string(endPosS1 - maxLength + maxLength);
}

void process()
{
    string s1 = "daxdnynytdnaxdnytnr";
    string s2 = "axdnytvab";

    cout << longestCommonSubstring(s1, s2);
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