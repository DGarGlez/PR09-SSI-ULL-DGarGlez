/**
 * 
 * REPOSITORIO: https://github.com/DGarGlez/PR09-SSI-ULL-DGarGlez.git
 * 
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Función para verificar si un número es primo (Lehman-Peralta)
bool esPrimo(int n) {
    if (n < 2) return false;    // Números menores que 2 no son primos
    for (int i = 2; i <= sqrt(n); ++i) {    // Verificar divisibilidad
        if (n % i == 0) return false;   // Si es divisible, no es primo
    }
    return true;    // Si no es divisible por ningún número, es primo
}

// Algoritmo de Euclides extendido
int euclidesExtendido(int a, int b, int &x, int &y) {
    if (b == 0) {   // Caso base
        x = 1;          // Inicializar x e y
        y = 0;          // Inicializar x e y
        return a;       // Retornar el GCD (Greatest Common Divisor) [Divisor Común Máximo]
    }
    // Llamada recursiva
    int x1, y1;     // Inicializar x1 e y1
    int gcd = euclidesExtendido(b, a % b, x1, y1);  // Calcular GCD (Greatest Common Divisor) [Divisor Común Máximo]
    x = y1;                 // Actualizar x e y
    y = x1 - (a / b) * y1;  // Actualizar x e y
    return gcd;      // Retornar el GCD (Greatest Common Divisor) [Divisor Común Máximo]
}

// Algoritmo de exponenciación rápida (Sin desbordamientos debido al uso de long long int)
long long int exponenciacionRapida(long long int base, long long int exponente, long long int mod) {
    long long int resultado = 1;    // Inicializar resultado
    base = base % mod;
    while (exponente > 0) {
        if (exponente % 2 == 1) {
            resultado = (resultado * base) % mod; // Aplicar módulo en cada multiplicación
        }
        exponente = exponente >> 1;
        base = (base * base) % mod; // Aplicar módulo en cada paso
    }
    return resultado;
}

// Función para convertir texto a bloques numéricos
vector<long long int> textoABloques(const string &texto, long long int j) {
    vector<long long int> bloques;
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string textoProcesado = texto;
    // Convertir a mayúsculas y eliminar espacios
    transform(textoProcesado.begin(), textoProcesado.end(), textoProcesado.begin(), ::toupper);
    textoProcesado.erase(remove_if(textoProcesado.begin(), textoProcesado.end(), ::isspace), textoProcesado.end());

    // Añadir X al final si el bloque no es del tamaño adecuado
    while (textoProcesado.size() % j != 0) {
        textoProcesado += 'X';
    }

    for (size_t i = 0; i < textoProcesado.size(); i += j) {
        int bloque = 0;
        for (int k = 0; k < j; ++k) {
            bloque = bloque * 26 + (alfabeto.find(textoProcesado[i + k]));
        }
        bloques.push_back(bloque);
    }
    return bloques;
}

int main() {
    string mensaje;
    int p, q, d;

    // Entrada del usuario
    cout << "Introduce el mensaje a cifrar: ";
    getline(cin, mensaje);
    cout << "Introduce p: ";
    cin >> p;
    cout << "Introduce q: ";
    cin >> q;
    cout << "Introduce d: ";
    cin >> d;

    // Verificar si p y q son primos
    if (!esPrimo(p) || !esPrimo(q)) {
        cout << "p o q no son primos." << endl;
        return 1;
    }
    cout << "p y q son primos." << endl;

    // Calcular n y φ(n)
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Verificar si d es primo con φ(n)
    int x, y;
    if (euclidesExtendido(d, phi, x, y) != 1) {
        cout << "d no es primo con φ(n)." << endl;
        return 1;
    }
    cout << "d es primo con φ(n) = " << phi << endl;

    // Calcular e usando el algoritmo de Euclides extendido
    int e;
    euclidesExtendido(d, phi, e, y);
    e = (e % phi + phi) % phi; // Asegurar que e sea positivo
    cout << "e calculado, e = " << e << endl;

    // Determinar el tamaño de los bloques
    int j = 1;
    while (pow(26, j) < n) {
        ++j;
    }
    --j;
    cout << "Como n = " << n << ", se divide el texto en bloques de " << j << " caracteres." << endl;

    // Convertir texto a bloques numéricos
    vector<long long int> bloques = textoABloques(mensaje, j);
    cout << "Bloques en decimal: ";
    for (int bloque : bloques) {
        cout << bloque << " ";
    }
    cout << endl;

    // Cifrar los bloques
    vector<long long int> bloquesCifrados;
    for (int bloque : bloques) {
        bloquesCifrados.push_back(exponenciacionRapida(bloque, e, n));
    }

    // Mostrar el texto cifrado
    cout << "Texto cifrado en decimal: ";
    for (long long int bloqueCifrado : bloquesCifrados) {
        cout << bloqueCifrado << " ";
    }
    cout << endl;

    return 0;
}