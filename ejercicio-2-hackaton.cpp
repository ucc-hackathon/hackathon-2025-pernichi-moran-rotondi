#include <iostream>
#include <ctime>
using namespace std;

class Item
{
public:
    string name;
    string type;
    int puntos;

    Item(string n, string t, int p) : name(n), type(t), puntos(p) {}
};

class Room
{
public:
    int id;
    string description;
    Room *norte;
    Room *sur;
    Room *este;
    Room *oeste;
    Item *item;

    Room(int i, string desc) : id(i), description(desc), norte(nullptr),
                               sur(nullptr), este(nullptr), oeste(nullptr), item(nullptr) {}

    void setItem(Item *i)
    {
        item = i;
    }

    Item *takeItem()
    {
        Item *temp = item;
        item = nullptr;
        return temp;
    }

    bool hasItem()
    {
        return item != nullptr;
    }
};

class Player
{
public:
    Room *currentRoom;
    Item *inventory[10];
    int itemCount;
    int pasos;
    int maxPasos;
    int puntaje;

    Player() : currentRoom(nullptr), itemCount(0), pasos(0), maxPasos(0), puntaje(0)
    {
        for (int i = 0; i < 10; i++)
        {
            inventory[i] = nullptr;
        }
    }

    void addItem(Item *item)
    {
        if (itemCount < 10)
        {
            inventory[itemCount] = item;
            itemCount++;
            puntaje += item->puntos;
        }
    }

    void showInventory()
    {
        if (itemCount == 0)
        {
            cout << "Tu inventario esta vacio." << endl;
            return;
        }

        cout << "\n=== INVENTARIO ===" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            cout << "- " << inventory[i]->name << " (" << inventory[i]->type
                 << ") [+" << inventory[i]->puntos << " pts]" << endl;
        }
        cout << "Puntaje total: " << puntaje << " puntos" << endl;
    }

    bool tienePasos()
    {
        return pasos < maxPasos;
    }

    void usarPaso()
    {
        pasos++;
    }
};


class Game
{
private:
    Room *rooms[7];
    Player player;
    bool running;

    void initializeGame()
    {
        player.maxPasos = 2 + (rand() % 4);

        rooms[0] = new Room(1, "Habitacion 1 - Entrada norte");
        rooms[1] = new Room(2, "Habitacion 2 - Entrada noreste");
        rooms[2] = new Room(3, "Habitacion 3 - Zona oeste");
        rooms[3] = new Room(4, "Habitacion 4 - Centro");
        rooms[4] = new Room(5, "Habitacion 5 - Zona este");
        rooms[5] = new Room(6, "Habitacion 6 - Sur centro");
        rooms[6] = new Room(7, "Habitacion 7 - Sur este");

        rooms[0]->sur = rooms[2];
        rooms[2]->norte = rooms[0];

        rooms[1]->sur = rooms[3];
        rooms[3]->norte = rooms[1];

        rooms[2]->este = rooms[3];
        rooms[3]->oeste = rooms[2];

        rooms[3]->este = rooms[4];
        rooms[4]->oeste = rooms[3];

        rooms[3]->sur = rooms[5];
        rooms[5]->norte = rooms[3];

        rooms[4]->sur = rooms[6];
        rooms[6]->norte = rooms[4];

        rooms[5]->este = rooms[6];
        rooms[6]->oeste = rooms[5];

        rooms[0]->setItem(new Item("manzana", "alimento", 1));
        rooms[1]->setItem(new Item("espada", "arma", 5));
        rooms[2]->setItem(new Item("pan", "alimento", 1));
        rooms[4]->setItem(new Item("escudo", "arma", 5));
        rooms[6]->setItem(new Item("pocion", "alimento", 1));

        player.currentRoom = rooms[2];
    }

    void showMap()
    {
        int pos = player.currentRoom->id;

        cout << "\n==================== MAPA ====================" << endl;
        cout << "                                              " << endl;
        cout << "     [" << (pos == 1 ? "*" : "1") << "]      [" << (pos == 2 ? "*" : "2") << "]                       " << endl;
        cout << "      |       |                               " << endl;
        cout << "     [" << (pos == 3 ? "*" : "3") << "]----[" << (pos == 4 ? "*" : "4") << "]----[" << (pos == 5 ? "*" : "5") << "]         " << endl;
        cout << "            |       |                         " << endl;
        cout << "           [" << (pos == 6 ? "*" : "6") << "]----[" << (pos == 7 ? "*" : "7") << "]                  " << endl;
        cout << "                                              " << endl;
        cout << "==============================================" << endl;
        cout << "Estas en: " << player.currentRoom->description << endl;
        cout << "Pasos: " << player.pasos << "/" << player.maxPasos
             << " | Puntaje: " << player.puntaje << endl;
    }

    void showCurrentRoom()
    {
        showMap();

        cout << "\nSalidas: ";
        if (player.currentRoom->norte)
            cout << "NORTE ";
        if (player.currentRoom->sur)
            cout << "SUR ";
        if (player.currentRoom->este)
            cout << "ESTE ";
        if (player.currentRoom->oeste)
            cout << "OESTE ";
        cout << endl;

        if (player.currentRoom->hasItem())
        {
            cout << "Ves un/a " << player.currentRoom->item->name
                 << " (" << player.currentRoom->item->type << ") [+"
                 << player.currentRoom->item->puntos << " pts]" << endl;
        }
    }

    void move(string direction)
    {
        if (!player.tienePasos())
        {
            cout << "\n¡Se acabaron los pasos! Juego terminado." << endl;
            endGame();
            return;
        }

        Room *nextRoom = nullptr;

        if (direction == "norte" || direction == "n")
        {
            nextRoom = player.currentRoom->norte;
        }
        else if (direction == "sur" || direction == "s")
        {
            nextRoom = player.currentRoom->sur;
        }
        else if (direction == "este" || direction == "e")
        {
            nextRoom = player.currentRoom->este;
        }
        else if (direction == "oeste" || direction == "o")
        {
            nextRoom = player.currentRoom->oeste;
        }

        if (nextRoom != nullptr)
        {
            player.currentRoom = nextRoom;
            player.usarPaso();
            cout << "\nTe has movido hacia el " << direction << "." << endl;
            showCurrentRoom();

            if (!player.tienePasos())
            {
                cout << "\n¡Se acabaron los pasos! Juego terminado." << endl;
                endGame();
            }
        }
        else
        {
            cout << "No puedes ir en esa direccion." << endl;
        }
    }

    void takeItem()
    {
        if (!player.currentRoom->hasItem())
        {
            cout << "No hay nada que tomar aqui." << endl;
            return;
        }

        Item *taken = player.currentRoom->takeItem();
        player.addItem(taken);
        cout << "Has tomado: " << taken->name << " (+" << taken->puntos << " puntos)" << endl;
        cout << "Puntaje actual: " << player.puntaje << endl;
    }

    void endGame()
    {
        running = false;

        cout << "\n============================================" << endl;
        cout << "           FIN DEL JUEGO                    " << endl;
        cout << "============================================" << endl;
        cout << "Pasos utilizados: " << player.pasos << "/" << player.maxPasos << endl;
        cout << "Items recolectados: " << player.itemCount << "/5" << endl;

        cout << "\n--- ITEMS OBTENIDOS ---" << endl;
        if (player.itemCount == 0)
        {
            cout << "No recolectaste ningun item." << endl;
        }
        else
        {
            for (int i = 0; i < player.itemCount; i++)
            {
                cout << "- " << player.inventory[i]->name
                     << " [+" << player.inventory[i]->puntos << " pts]" << endl;
            }
        }

        cout << "\n*** PUNTAJE FINAL: " << player.puntaje << " PUNTOS ***" << endl;

        if (player.puntaje >= 17)
        {
            cout << "¡PERFECTO! Recolectaste todos los items." << endl;
        }
        else if (player.puntaje >= 12)
        {
            cout << "¡Excelente! Buen trabajo." << endl;
        }
        else if (player.puntaje >= 6)
        {
            cout << "Bien hecho, pero puedes mejorar." << endl;
        }
        else
        {
            cout << "Intenta recolectar mas items la proxima vez." << endl;
        }

        cout << "============================================" << endl;
    }

    void processCommand(string input)
    {
        for (size_t i = 0; i < input.length(); i++)
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
            {
                input[i] = input[i] + 32;
            }
        }

        if (input == "norte" || input == "n")
        {
            move("norte");
        }
        else if (input == "sur" || input == "s")
        {
            move("sur");
        }
        else if (input == "este" || input == "e")
        {
            move("este");
        }
        else if (input == "oeste" || input == "o")
        {
            move("oeste");
        }
        else if (input == "tomar" || input == "t")
        {
            takeItem();
        }
        else if (input == "inventario" || input == "i")
        {
            player.showInventory();
        }
        else if (input == "mapa" || input == "m")
        {
            showCurrentRoom();
        }
        else if (input == "ayuda" || input == "h")
        {
            showHelp();
        }
        else if (input == "salir" || input == "q")
        {
            endGame();
        }
        else
        {
            cout << "Comando no reconocido. Escribe 'ayuda' para ver los comandos." << endl;
        }
    }

    void showHelp()
    {
        cout << "\n=== COMANDOS DISPONIBLES ===" << endl;
        cout << "norte/n, sur/s, este/e, oeste/o - Moverte (usa 1 paso)" << endl;
        cout << "tomar/t - Tomar objeto en la habitacion" << endl;
        cout << "inventario/i - Ver tu inventario" << endl;
        cout << "mapa/m - Ver el mapa" << endl;
        cout << "ayuda/h - Mostrar esta ayuda" << endl;
        cout << "salir/q - Salir del juego" << endl;
    }

public:
    Game() : running(true)
    {
        initializeGame();
    }

    ~Game()
    {
        for (int i = 0; i < 7; i++)
        {
            if (rooms[i]->item != nullptr)
            {
                delete rooms[i]->item;
            }
            delete rooms[i];
        }

        for (int i = 0; i < player.itemCount; i++)
        {
            delete player.inventory[i];
        }
    }

    void start()
    {
        cout << "========================================" << endl;
        cout << "      JUEGO DE AVENTURA - EDIFICIO     " << endl;
        cout << "========================================" << endl;
        cout << "Bienvenido al edificio misterioso..." << endl;
        cout << "Tienes " << player.maxPasos << " pasos para recolectar items." << endl;
        cout << "Escribe 'ayuda' para ver los comandos." << endl;

        showCurrentRoom();

        string input;
        while (running)
        {
            cout << "\n> ";
            getline(cin, input);

            if (!input.empty())
            {
                processCommand(input);
            }
        }
    }
};

int main()
{
    srand(time(0));
    Game game;
    game.start();
}