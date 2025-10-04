#include <iostream>
using namespace std;

class Equipo {
private:
    string nombre;

public:
    Equipo(string n);
    string getNombre() const;
};
 Equipo :: Equipo(string n) : nombre(n) {}
  string Equipo::  getNombre() const { return nombre; }
class Partido {
private:
    Equipo equipo1;
    Equipo equipo2;
    int golesEquipo1;
    int golesEquipo2;

public:
    Partido(Equipo eq1, Equipo eq2, int g1, int g2);
    Equipo getEquipo1() const;
    Equipo getEquipo2() const;
    int getGolesEquipo1() const;
    int getGolesEquipo2() const;
};
    Partido::Partido(Equipo eq1, Equipo eq2, int g1, int g2) : equipo1(eq1), equipo2(eq2), golesEquipo1(g1), golesEquipo2(g2) {}
    Equipo Partido:: getEquipo1() const { return equipo1; }
    Equipo Partido::getEquipo2() const { return equipo2; }
    int Partido ::getGolesEquipo1() const { return golesEquipo1; }
    int Partido ::getGolesEquipo2() const { return golesEquipo2; }
struct ResultadoEquipo {
    string nombre;
    int puntos;
    int golesAFavor;
    int golesEnContra;

    int diferenciaGoles() const {
        return golesAFavor - golesEnContra;
    }
};


void ordenarTabla(ResultadoEquipo tabla[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool cambiar = false;

            
            if (tabla[j].puntos < tabla[j + 1].puntos) {
                cambiar = true;
            }
            
            else if (tabla[j].puntos == tabla[j + 1].puntos) {
                if (tabla[j].diferenciaGoles() < tabla[j + 1].diferenciaGoles()) {
                    cambiar = true;
                }
                
                else if (tabla[j].diferenciaGoles() == tabla[j + 1].diferenciaGoles()) {
                    if (tabla[j].golesAFavor < tabla[j + 1].golesAFavor) {
                        cambiar = true;
                    }
                }
            }

            if (cambiar) {
                ResultadoEquipo temp = tabla[j];
                tabla[j] = tabla[j + 1];
                tabla[j + 1] = temp;
            }
        }
    }
}

int main() {
    Equipo equipos[6] = {
        Equipo("UCC"), Equipo("UNC"), Equipo("UTN"),
        Equipo("UNRC"), Equipo("UBP"), Equipo("UES21")
    };

    Partido partidos[15] = {
        Partido(equipos[3], equipos[4], 0, 0),
        Partido(equipos[0], equipos[3], 3, 0),
        Partido(equipos[2], equipos[4], 2, 2),
        Partido(equipos[1], equipos[5], 3, 1),
        Partido(equipos[4], equipos[5], 2, 1),
        Partido(equipos[0], equipos[2], 4, 1),
        Partido(equipos[1], equipos[3], 2, 2),
        Partido(equipos[0], equipos[4], 0, 2),
        Partido(equipos[1], equipos[2], 0, 1),
        Partido(equipos[2], equipos[3], 0, 1),
        Partido(equipos[0], equipos[1], 2, 1),
        Partido(equipos[0], equipos[5], 2, 2),
        Partido(equipos[1], equipos[4], 1, 3),
        Partido(equipos[2], equipos[5], 1, 0),
        Partido(equipos[3], equipos[5], 2, 3)
    };

    ResultadoEquipo tabla[6];
    for (int i = 0; i < 6; i++) {
        tabla[i] = {equipos[i].getNombre(), 0, 0, 0};
    }

    cout << "=== RESULTADOS DE LOS PARTIDOS ===\n\n";
    for (int i = 0; i < 15; i++) {
        string eq1 = partidos[i].getEquipo1().getNombre();
        string eq2 = partidos[i].getEquipo2().getNombre();
        int g1 = partidos[i].getGolesEquipo1();
        int g2 = partidos[i].getGolesEquipo2();

        cout << "Partido " << (i + 1) << ": " << eq1 << " " << g1
             << " - " << g2 << " " << eq2 << endl;

        for (int j = 0; j < 6; j++) {
            if (tabla[j].nombre == eq1) {
                tabla[j].golesAFavor += g1;
                tabla[j].golesEnContra += g2;
                if (g1 > g2) tabla[j].puntos += 3;
                else if (g1 == g2) tabla[j].puntos += 1;
            }
            if (tabla[j].nombre == eq2) {
                tabla[j].golesAFavor += g2;
                tabla[j].golesEnContra += g1;
                if (g2 > g1) tabla[j].puntos += 3;
                else if (g1 == g2) tabla[j].puntos += 1;
            }
        }
    }

    ordenarTabla(tabla, 6);

    cout << "\n=== TABLA DE POSICIONES ===\n\n";
    cout << "Pos | Equipo | Pts | GF | GC | DG\n";
    cout << "----+--------+-----+----+----+----\n";

    for (int i = 0; i < 6; i++) {
        cout << " " << (i + 1) << "  | " << tabla[i].nombre;
        for (int k = tabla[i].nombre.length(); k < 6; k++) cout << " ";
        cout << " | " << tabla[i].puntos;
        if (tabla[i].puntos < 10) cout << " ";
        cout << "  | " << tabla[i].golesAFavor;
        if (tabla[i].golesAFavor < 10) cout << " ";
        cout << " | " << tabla[i].golesEnContra;
        if (tabla[i].golesEnContra < 10) cout << " ";
        cout << " | " << tabla[i].diferenciaGoles() << endl;
    }

    cout << "\n=== PODIO ===\n";
    cout << "1er lugar: " << tabla[0].nombre << " (" << tabla[0].puntos << " puntos)\n";
    cout << "2do lugar: " << tabla[1].nombre << " (" << tabla[1].puntos << " puntos)\n";
    cout << "3er lugar: " << tabla[2].nombre << " (" << tabla[2].puntos << " puntos)\n";

}