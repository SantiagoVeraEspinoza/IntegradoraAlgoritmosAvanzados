#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

/*
Datos:
- Nombres:
    + Santiago Vera Espinoza - A01641585
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
void printVector(vector<int> input)
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

int process()
{
    string root_dir;

    cout << "Inserta el directorio a analizar: "; // Directorio a analizar
    cin >> root_dir;
    cout << endl;

    DIR* dir = opendir(root_dir.c_str()); // Abrir el directorio

    if (!dir) { // Intenta abrir el directorio
        std::cerr << "Failed to open directory." << std::endl;
        return 1;
    }

    cout << root_dir;

    struct dirent* entry; // Itera por el directorio
    while ((entry = readdir(dir)) != nullptr) {
        string file_path = root_dir + entry->d_name;

        struct stat file_info;
        cout << endl << entry->d_name << " - " << file_path << " - " << DT_REG;
        if (entry->d_type == DT_REG) {
            // Process regular files (not directories)
            cout << "File: " << entry->d_name << std::endl;
        }
    }

    //string res = KMP(str, pat); // Ejecuta el método KMP - O(n+m)

    //cout << endl << res << endl;
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