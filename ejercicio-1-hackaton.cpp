#include <iostream>
using namespace std;

class Usuario
{
private:
    long legajo;

public:
    Usuario();
    Usuario(long l);
    void setlegajo(long l);
    long getlegajo() const;
    virtual string tipoUsuario() const = 0;
    virtual ~Usuario();
};

class Libro
{
private:
    long codigo;
    string titulo;
    string autor;
    int anio;
    string categoria;
    bool prestado;
    long legajoPrestamo;
    string tipoPrestamo;
    int vecesPrestado;

public:
    Libro();
    Libro(long c, string t, string au, int a, string cat);
    void setcodigo(long c);
    void settitulo(string t);
    void setautor(string au);
    void setanio(int a);
    void setcategoria(string cat);
    long getcodigo();
    string gettitulo();
    string getautor();
    int getanio();
    string getcategoria();
    bool estarprestado();
    bool prestar(const Usuario &u);
    bool devolver();
    int getVecesPrestado();
    long getLegajoPrestamo();
    void mostrar();
    ~Libro();
};

class Alumno : public Usuario
{
private:
    int anio;

public:
    Alumno();
    Alumno(long l, int a);
    void setanio(int a);
    int getanio();
    string tipoUsuario() const override;
    ~Alumno();
};

class Profesor : public Usuario
{
private:
    string area;

public:
    Profesor();
    Profesor(long l, string a);
    void setarea(string a);
    string getarea();
    string tipoUsuario() const override;
    ~Profesor();
};

void listarDisponibles(Libro libros[], int cant);
void listarPrestados(Libro libros[], int cant);
void buscarPorCategoria(Libro libros[], int cant, string cat);
void buscarPorAutor(Libro libros[], int cant, string autor);
void top3Prestados(Libro libros[], int cant);
void usuarioMasPrestamos(Libro libros[], int cant);

Libro::Libro()
{
    codigo = 0;
    titulo = "";
    autor = "";
    anio = 0;
    categoria = "";
    prestado = false;
    legajoPrestamo = 0;
    tipoPrestamo = "";
    vecesPrestado = 0;
}

Libro::Libro(long c, string t, string au, int a, string cat)
{
    codigo = c;
    titulo = t;
    autor = au;
    anio = a;
    categoria = cat;
    prestado = false;
    legajoPrestamo = 0;
    tipoPrestamo = "";
    vecesPrestado = 0;
}

void Libro::setcodigo(long c) { codigo = c; }
void Libro::settitulo(string t) { titulo = t; }
void Libro::setautor(string au) { autor = au; }
void Libro::setanio(int a) { anio = a; }
void Libro::setcategoria(string cat) { categoria = cat; }
long Libro::getcodigo() { return codigo; }
string Libro::gettitulo() { return titulo; }
string Libro::getautor() { return autor; }
int Libro::getanio() { return anio; }
string Libro::getcategoria() { return categoria; }
bool Libro::estarprestado() { return prestado; }
int Libro::getVecesPrestado() { return vecesPrestado; }
long Libro::getLegajoPrestamo() { return legajoPrestamo; }

bool Libro::prestar(const Usuario &u)
{
    if (prestado)
        return false;
    prestado = true;
    legajoPrestamo = u.getlegajo();
    tipoPrestamo = u.tipoUsuario();
    vecesPrestado++;
    return true;
}

bool Libro::devolver()
{
    if (!prestado)
        return false;
    prestado = false;
    legajoPrestamo = 0;
    tipoPrestamo = "";
    return true;
}

void Libro::mostrar()
{
    cout << "[" << codigo << "] " << titulo << " - " << autor << " (" << categoria << ")";
}

Libro::~Libro() {}

Usuario::Usuario() { legajo = 0; }
Usuario::Usuario(long l) { legajo = l; }
void Usuario::setlegajo(long l) { legajo = l; }
long Usuario::getlegajo() const { return legajo; }
Usuario::~Usuario() {}

Alumno::Alumno()
{
    setlegajo(0);
    anio = 0;
}
Alumno::Alumno(long l, int a)
{
    setlegajo(l);
    anio = a;
}
void Alumno::setanio(int a) { anio = a; }
int Alumno::getanio() { return anio; }
string Alumno::tipoUsuario() const { return "Alumno"; }
Alumno::~Alumno() {}

Profesor::Profesor()
{
    setlegajo(0);
    area = "";
}
Profesor::Profesor(long l, string a)
{
    setlegajo(l);
    area = a;
}
void Profesor::setarea(string a) { area = a; }
string Profesor::getarea() { return area; }
string Profesor::tipoUsuario() const { return "Profesor"; }
Profesor::~Profesor() {}

void listarDisponibles(Libro libros[], int cant)
{
    cout << "\n=== LIBROS DISPONIBLES ===" << endl;
    for (int i = 0; i < cant; i++)
    {
        if (!libros[i].estarprestado())
        {
            libros[i].mostrar();
            cout << " - DISPONIBLE" << endl;
        }
    }
}

void listarPrestados(Libro libros[], int cant)
{
    cout << "\n=== LIBROS PRESTADOS ===" << endl;
    for (int i = 0; i < cant; i++)
    {
        if (libros[i].estarprestado())
        {
            libros[i].mostrar();
            cout << " - PRESTADO" << endl;
        }
    }
}

void buscarPorCategoria(Libro libros[], int cant, string cat)
{
    cout << "\n=== BUSCAR POR CATEGORIA: " << cat << " ===" << endl;
    for (int i = 0; i < cant; i++)
    {
        if (libros[i].getcategoria() == cat)
        {
            libros[i].mostrar();
            cout << " - " << (libros[i].estarprestado() ? "PRESTADO" : "DISPONIBLE") << endl;
        }
    }
}

void buscarPorAutor(Libro libros[], int cant, string autor)
{
    cout << "\n=== BUSCAR POR AUTOR: " << autor << " ===" << endl;
    for (int i = 0; i < cant; i++)
    {
        if (libros[i].getautor() == autor)
        {
            libros[i].mostrar();
            cout << " - " << (libros[i].estarprestado() ? "PRESTADO" : "DISPONIBLE") << endl;
        }
    }
}

void top3Prestados(Libro libros[], int cant)
{
    cout << "\n=== TOP 3 LIBROS MAS PRESTADOS ===" << endl;

    Libro temp[50];
    for (int i = 0; i < cant; i++)
    {
        temp[i] = libros[i];
    }

    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = 0; j < cant - i - 1; j++)
        {
            if (temp[j].getVecesPrestado() < temp[j + 1].getVecesPrestado())
            {
                Libro aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    int limite = (cant < 3) ? cant : 3;
    for (int i = 0; i < limite; i++)
    {
        cout << (i + 1) << ". ";
        temp[i].mostrar();
        cout << " - " << temp[i].getVecesPrestado() << " prestamos" << endl;
    }
}

void usuarioMasPrestamos(Libro libros[], int cant)
{
    cout << "\n=== USUARIO CON MAS PRESTAMOS ===" << endl;

    long legajos[100];
    int contadores[100];
    int numUsuarios = 0;

    for (int i = 0; i < cant; i++)
    {
        int veces = libros[i].getVecesPrestado();
        if (veces == 0)
            continue;

        if (libros[i].estarprestado())
        {
            long leg = libros[i].getLegajoPrestamo();
            bool encontrado = false;

            for (int j = 0; j < numUsuarios; j++)
            {
                if (legajos[j] == leg)
                {
                    contadores[j]++;
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado && numUsuarios < 100)
            {
                legajos[numUsuarios] = leg;
                contadores[numUsuarios] = 1;
                numUsuarios++;
            }
        }
    }

    if (numUsuarios > 0)
    {
        int maxIdx = 0;
        for (int i = 1; i < numUsuarios; i++)
        {
            if (contadores[i] > contadores[maxIdx])
            {
                maxIdx = i;
            }
        }
        cout << "Usuario con legajo " << legajos[maxIdx]
             << " tiene " << contadores[maxIdx] << " libros prestados actualmente." << endl;
    }
    else
    {
        cout << "No hay prestamos activos." << endl;
    }
}

int main()
{
    cout << "\n=== SISTEMA DE BIBLIOTECA ===" << endl;

    Alumno a1(123, 2025);
    Alumno a2(124, 2024);
    Profesor p1(456, "Matematica");
    Profesor p2(457, "Fisica");

    Libro libros[8];
    libros[0] = Libro(1001, "C++ Programming", "Stroustrup", 2013, "POO");
    libros[1] = Libro(1002, "Algoritmos", "Cormen", 2009, "Algoritmos");
    libros[2] = Libro(1003, "Clean Code", "Martin", 2008, "POO");
    libros[3] = Libro(1004, "Base de Datos", "Silberschatz", 2011, "BD");
    libros[4] = Libro(1005, "Redes", "Tanenbaum", 2003, "Redes");
    libros[5] = Libro(1006, "Estructura de Datos", "Cormen", 2012, "Algoritmos");
    libros[6] = Libro(1007, "Design Patterns", "Gamma", 1994, "POO");
    libros[7] = Libro(1008, "IA Moderna", "Russell", 2010, "IA");

    int opcion;
    bool salir = false;

    while (!salir)
    {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Prestar libro" << endl;
        cout << "2. Devolver libro" << endl;
        cout << "3. Listar libros disponibles" << endl;
        cout << "4. Listar libros prestados" << endl;
        cout << "5. Buscar por categoria" << endl;
        cout << "6. Buscar por autor" << endl;
        cout << "7. Ver top 3 mas prestados" << endl;
        cout << "8. Ver usuario con mas prestamos" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1)
        {
            long codigo;
            cout << "\nIngrese codigo del libro: ";
            cin >> codigo;

            int idx = -1;
            for (int i = 0; i < 8; i++)
            {
                if (libros[i].getcodigo() == codigo)
                {
                    idx = i;
                    break;
                }
            }

            if (idx == -1)
            {
                cout << "Libro no encontrado." << endl;
            }
            else if (libros[idx].estarprestado())
            {
                cout << "El libro ya esta prestado." << endl;
            }
            else
            {
                cout << "Usuarios disponibles:" << endl;
                cout << "1. Alumno 123" << endl;
                cout << "2. Alumno 124" << endl;
                cout << "3. Profesor 456" << endl;
                cout << "4. Profesor 457" << endl;
                int usr;
                cout << "Seleccione usuario: ";
                cin >> usr;

                bool exito = false;
                if (usr == 1)
                    exito = libros[idx].prestar(a1);
                else if (usr == 2)
                    exito = libros[idx].prestar(a2);
                else if (usr == 3)
                    exito = libros[idx].prestar(p1);
                else if (usr == 4)
                    exito = libros[idx].prestar(p2);

                if (exito)
                    cout << "Libro prestado exitosamente!" << endl;
                else
                    cout << "Error al prestar el libro." << endl;
            }
        }
        else if (opcion == 2)
        {
            long codigo;
            cout << "\nIngrese codigo del libro a devolver: ";
            cin >> codigo;

            int idx = -1;
            for (int i = 0; i < 8; i++)
            {
                if (libros[i].getcodigo() == codigo)
                {
                    idx = i;
                    break;
                }
            }

            if (idx == -1)
            {
                cout << "Libro no encontrado." << endl;
            }
            else
            {
                if (libros[idx].devolver())
                {
                    cout << "Libro devuelto exitosamente!" << endl;
                }
                else
                {
                    cout << "El libro no estaba prestado." << endl;
                }
            }
        }
        else if (opcion == 3)
        {
            listarDisponibles(libros, 8);
        }
        else if (opcion == 4)
        {
            listarPrestados(libros, 8);
        }
        else if (opcion == 5)
        {
            string cat;
            cout << "\nIngrese categoria (POO/Algoritmos/BD/Redes/IA): ";
            cin >> cat;
            buscarPorCategoria(libros, 8, cat);
        }
        else if (opcion == 6)
        {
            string autor;
            cout << "\nIngrese autor: ";
            cin.ignore();
            getline(cin, autor);
            buscarPorAutor(libros, 8, autor);
        }
        else if (opcion == 7)
        {
            top3Prestados(libros, 8);
        }
        else if (opcion == 8)
        {
            usuarioMasPrestamos(libros, 8);
        }
        else if (opcion == 0)
        {
            salir = true;
            cout << "\nGracias por usar el sistema!" << endl;
        }
        else
        {
            cout << "Opcion invalida." << endl;
        }
    }
}