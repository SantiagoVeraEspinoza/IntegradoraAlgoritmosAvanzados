#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

/*
Datos:
- Nombres:
    + Santiago Vera Espinoza - A01641585
    + Carlos Isaac Dávalos Lomelí - A01706041
    + Luis Portillo López - A00829935
- Fecha: 27/08/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Cantidad de letras en palabra
- m: Cantidad de letras en patrón
- v: Cantidad de elmentos en vector
*/

// Imprime un vector - O(v)
template <typename T>
void printVector(vector<T> input)
{
    cout << "Vector = [";
    for (int i=0; i<input.size(); i++) // Itera por el vector - O(v)
    {
        if (i >= input.size() - 1) 
        {
            cout << input[i];
            continue;
        }
        cout << input[i] << ", ";
    }
    cout << "]" << endl; 
}

// <consigue el código del patrón para el KMP - O(m)
vector<int> getKMPCode(string input)
{
    vector<int> code; // Código para el KMP

    int i = 1; // Un puntero al caracter igual
    int len = 0; // Un puntero al elemento actual del prefijo
    code.push_back(0); // Añade un cero al primer elemento

    while(i < input.size()) // Itera por todo el patrón - O(m)
    {
        if (input[i] == input[len]) // Si ambos valores apuntados son iguales se añade el actual valor del puntero más uno al código
        {
            len++;
            code.push_back(len);
            i++; // También incrementa el puntero de caracter
            continue;
        }
        if (len > 0) // Si no son iguales pero el puntero de prefijo es mayor a uno se regresa al codigo apuntado por el elemento anterior
        { // En el peor de los casos se ejecuta dos veces, lo cual es constante y no afecta a la complejidad
            len = code[len - 1];
            continue;
        }
        code.push_back(0); // En cualquier otro caso se agrega un cero
        i++;
    }

    return code; // Regresa el código obtenido
}

// Proceso KMP - O(n+m)
string KMP(string str, string pat)
{
    int i = 0;
    int j = 0;
    int count = 0;

    vector <int> code = getKMPCode(pat); // Obtiene el vector código - O(m)

    while (i <= str.size()) // Itera por toda la cadena principal - O(n)
    {
        if (j >= pat.size()) // Ecuentra una solución
        {
            count++;
            j = code[j - 1];

            return "true " + to_string(i - pat.size());

            continue;
        }
        if (i >= str.size())  // Se excede el tamaño del patrón
        {
            if (count <= 0) return "false";
            return "true";
        }
        if (str[i] == pat[j]) // Se encuentra una coincidencia
        {
            i++;
            j++;
            continue;
        }
        if (j != 0){ // Se regresa el puntero del patrón en caso de no coincidir con el puntero del índice
            // En el peor de los casos se ejecutara sólo 2 veces, por lo que se puede considerar O(1)
            j = code[j - 1];
            continue;
        }
        i++; // En cualquier otro caso sólo aumenta el índice
    }

    return "false";
}

// Espejear string - O(n)
string mirrorString(string input) {
    int length = input.length();
    string mirrored = input;

    for (int i = 0; i < length / 2; i++) { // Itera por el string - O(n/2) = O(n)
        swap(mirrored[i], mirrored[length - i - 1]);
    }

    return input + mirrored;
}

// Separa con un delimitador - O(n)
vector <string> split(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(input);
    string token;

    while (getline(tokenStream, token, delimiter)) { // Itera por el string y evita los delimitadores - O(n)
        tokens.push_back(token);
    }

    return tokens;
}

// Encuentra el substring común más largo - O(nm)
string longestCommonSubstring(const string &s1, const string &s2) {
    int n = s1.length();
    int m = s2.length();

    // Usar dos filas en lugar de la matriz completa para dp
    vector<vector<int>> dp(2, vector<int>(m + 1, 0));

    int maxLength = 0; // Almacena la longitud de la subcadena más larga
    int endPosS1 = 0;  // Para almacenar el índice del carácter final en s1 de LCS

    // Llena la tabla
    for (int i = 1; i <= n; i++) { // Itera por ambas strings - O(nm)
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) { // Si encuentra una string igual actualiza el dp
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1;
                if (dp[i % 2][j] > maxLength) {
                    maxLength = dp[i % 2][j];
                    endPosS1 = i;
                }
            } else {
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

// Proceso principal - O()
int process()
{
    string root_dir; // String con el root dir

    cout << "Inserta el directorio a analizar: "; // Directorio a analizar
    cin >> root_dir;
    cout << endl;

    DIR* dir = opendir(root_dir.c_str()); // Abrir el directorio

    if (!dir) { // Intenta abrir el directorio
        std::cerr << "Failed to open directory." << std::endl;
        return 1;
    }

    cout << endl << "Parte 1:" << endl; // Comienza la parte 1

    vector <string> patterns; // Vector para los patrones y las transmisiones
    vector <string> transmissions;

    struct dirent* entry; // Itera por el directorio
    while ((entry = readdir(dir)) != nullptr) { // Itera por los archivos maliciosos (m) y por los códigos (n) - O(2n + 3m) = O(n + m)
        string file_path = root_dir + entry->d_name; // General el path relativo

        if ((KMP(file_path, "/.") != "false") || (KMP(entry->d_name, "..") != "false")) // Evita los directorios referencia
        {
            continue;
        }

        if ((KMP(file_path, "mcode") != "false")) // Lee el Mcode
        {
            fstream input_file(file_path);

            if (!input_file.is_open()) { // Checa si el archivo existe
                std::cerr << "Error opening file: " << file_path << std::endl;
                return 1;
            }

            string line;
            while (std::getline(input_file, line)) { // Obtiene la linea - O(m)
                patterns.push_back(line); // Pushea al vector - O(1)
            }

            input_file.close();
            continue;
        }

        if (KMP(file_path, "transmission") != "false") // Lee la transmición
        {
            fstream input_file(file_path);

            if (!input_file.is_open()) { // Checa si el archivo existe
                std::cerr << "Error opening file: " << file_path << std::endl;
                return 1;
            }

            string line;
            while (std::getline(input_file, line)) { // Obtiene la linea - O(n)
                transmissions.push_back(line); // Pushea al vector - O(1)
            }

            input_file.close();
            continue;
        }
    }

    int cont = 1;
    // Itera por cada transmisión - O(2) = O(n+m)
    for (auto e : transmissions) {
        cout << endl << "Para transmission" << cont << ".txt:" << endl;

        int cont2 = 1;
        for (auto p : patterns) // Itera por cada patrón - O(3)
        {
            string originalResult = KMP(e, p); // Busca el patrón original - O(n+m)

            cout << "Código " << cont2 << ": " << originalResult << endl;

            cont2++;
        }
        cont++;

    }

    cout << endl << "Parte 2:" << endl; // Comienza la parte 2

    cont = 1;
    // Itera por cada transmisión - O(2) = O(n+m)
    for (auto e : transmissions) {
        cout << endl << "Para transmission" << cont << ".txt:" << endl;

        int cont2 = 1;
        pair <int, string> max = {-1, "-1"};
        for (auto p : patterns) // Itera por cada patrón - O(3)
        {
            string mirroredString = mirrorString(p); // Espejea (obtiene el palíndromo) de el código malicioso - O(n)
            string mirroredResult = KMP(e, mirroredString); // Busca el patrón espejeado - O(n+m)

            if (mirroredResult != "false") {
                vector <string> result = split(mirroredResult, ' '); // Divide el string - O(n)

                mirroredResult = "Coincidencia máxima en rango: " + to_string(stoi(result[1]) + 1) + " " + to_string(stoi(result[1]) + mirroredString.size() + 1);

                if (max.first = -1) max = {mirroredString.size(), mirroredResult};

                if (mirroredString.size() > max.first) max = {mirroredString.size(), mirroredResult};
            }

            cont2++;
        }

        cout << max.second << endl;

        cont++;
    }

    cout << endl << "Parte 3:" << endl; // Comienza la parte 3

    cout << "Substring más largo entre los archivos de transmisión:" << endl;
    // cout << transmissions[0] << endl << "------------------" << endl << transmissions[1] << endl;
    cout << longestCommonSubstring(transmissions[0], transmissions[1]);
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