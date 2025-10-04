#include <iostream>
using namespace std;

string obtenerPieza(int ascii)
{
    switch (ascii)
    {
    case 185:
        return "║";
    case 186:
        return "║";
    case 187:
        return "╗";
    case 188:
        return "╝";
    case 200:
        return "╚";
    case 201:
        return "╔";
    case 202:
        return "╩";
    case 203:
        return "╦";
    case 204:
        return "╠";
    case 205:
        return "═";
    case 206:
        return "╬";
    default:
        return " ";
    }
}

int asciiAIndice(int ascii)
{
    int codigos[] = {185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};
    for (int i = 0; i < 11; i++)
    {
        if (codigos[i] == ascii)
            return i;
    }
    return -1;
}


bool conectan(int pieza1, int pieza2, string direccion)
{
    bool conexiones[12][4] = {
        {0, 1, 0, 1}, 
        {0, 1, 0, 1}, 
        {0, 1, 1, 0}, 
        {0, 0, 1, 1}, 
        {1, 0, 0, 1}, 
        {1, 1, 0, 0}, 
        {1, 0, 1, 1}, 
        {1, 1, 1, 0}, 
        {0, 1, 1, 1}, 
        {1, 0, 1, 0},
        {1, 1, 1, 1},
    };

    int idx1 = asciiAIndice(pieza1);
    int idx2 = asciiAIndice(pieza2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    if (direccion == "derecha")
        return conexiones[idx1][0] && conexiones[idx2][2];
    if (direccion == "abajo")
        return conexiones[idx1][1] && conexiones[idx2][3];
    if (direccion == "izquierda")
        return conexiones[idx1][2] && conexiones[idx2][0];
    if (direccion == "arriba")
        return conexiones[idx1][3] && conexiones[idx2][1];

    return false;
}

int calcularPuntos(int tablero[][20], bool visitado[][20], int n, int fila, int col)
{
    if (fila < 0 || fila >= n || col < 0 || col >= n)
        return 0;
    if (visitado[fila][col] || tablero[fila][col] == 0)
        return 0;

    visitado[fila][col] = true;
    int puntos = 1;
    int pieza = tablero[fila][col];

    if (col + 1 < n && tablero[fila][col + 1] != 0 &&
        conectan(pieza, tablero[fila][col + 1], "derecha"))
    {
        puntos += calcularPuntos(tablero, visitado, n, fila, col + 1);
    }
    if (fila + 1 < n && tablero[fila + 1][col] != 0 &&
        conectan(pieza, tablero[fila + 1][col], "abajo"))
    {
        puntos += calcularPuntos(tablero, visitado, n, fila + 1, col);
    }
    if (col - 1 >= 0 && tablero[fila][col - 1] != 0 &&
        conectan(pieza, tablero[fila][col - 1], "izquierda"))
    {
        puntos += calcularPuntos(tablero, visitado, n, fila, col - 1);
    }
    if (fila - 1 >= 0 && tablero[fila - 1][col] != 0 &&
        conectan(pieza, tablero[fila - 1][col], "arriba"))
    {
        puntos += calcularPuntos(tablero, visitado, n, fila - 1, col);
    }

    return puntos;
}

void mostrarTablero(int tablero[][20], int n)
{
    cout << "\n  ";
    for (int j = 0; j < n; j++)
    {
        cout << j + 1 << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "|";
        for (int j = 0; j < n; j++)
        {
            if (tablero[i][j] == 0)
            {
                cout << "  ";
            }
            else
            {
                cout << obtenerPieza(tablero[i][j]) << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Ingrese valor del tablero (8-20): ";
    cin >> n;

    if (n < 8 || n > 20)
    {
        cout << "Tablero debe ser entre 8x8 y 20x20\n";
        return 1;
    }

    int tablero[20][20] = {0};
    int piezas[32];
    int numPiezas = (n * n <= 32) ? n * n : 32;

    int codigosValidos[] = {185, 186, 187, 188, 200, 201, 202, 203, 204, 205, 206};
    cout << "\nPiezas asignadas: ";
    for (int i = 0; i < numPiezas; i++)
    {
        piezas[i] = codigosValidos[rand() % 11];
        cout << piezas[i] << " ";
    }
    cout << endl;

    mostrarTablero(tablero, n);

    int piezaIdx = 0;
    int puntosJugador = 0;
    int puntosComputadora = 0;
    bool turnoJugador = true;

    while (piezaIdx < numPiezas)
    {
        if (turnoJugador)
        {
            cout << "\n--- TURNO JUGADOR ---\n";
            cout << "Pieza actual: " << obtenerPieza(piezas[piezaIdx])
                 << " (ASCII: " << piezas[piezaIdx] << ")\n";

            int fila, col;
            cout << "Ingrese posicion (fila col): ";
            cin >> fila >> col;
            fila--;
            col--;

            if (fila < 0 || fila >= n || col < 0 || col >= n || tablero[fila][col] != 0)
            {
                cout << "Posicion invalida!\n";
                continue;
            }

            tablero[fila][col] = piezas[piezaIdx];

            bool visitado[20][20] = {false};
            int puntos = calcularPuntos(tablero, visitado, n, fila, col);
            puntosJugador += puntos * puntos;

            cout << "Puntos obtenidos: " << puntos * puntos << " (fragmento de " << puntos << ")\n";
            cout << "Total jugador: " << puntosJugador << endl;
        }
        else
        {
            cout << "\n--- TURNO COMPUTADORA ---\n";
            int fila, col;
            do
            {
                fila = rand() % n;
                col = rand() % n;
            } while (tablero[fila][col] != 0);

            tablero[fila][col] = piezas[piezaIdx];
            cout << "Computadora coloca en (" << fila + 1 << "," << col + 1 << ")\n";

            bool visitado[20][20] = {false};
            int puntos = calcularPuntos(tablero, visitado, n, fila, col);
            puntosComputadora += puntos * puntos;

            cout << "Puntos computadora: " << puntos * puntos << endl;
            cout << "Total computadora: " << puntosComputadora << endl;
        }

        mostrarTablero(tablero, n);
        piezaIdx++;
        turnoJugador = !turnoJugador;
    }

    cout << "\n=== JUEGO TERMINADO ===\n";
    cout << "Puntos Jugador: " << puntosJugador << endl;
    cout << "Puntos Computadora: " << puntosComputadora << endl;

    if (puntosJugador > puntosComputadora)
    {
        cout << "¡GANASTE!\n";
    }
    else if (puntosComputadora > puntosJugador)
    {
        cout << "Gano la computadora\n";
    }
    else
    {
        cout << "¡EMPATE!\n";
    }
}