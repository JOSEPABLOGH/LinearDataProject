//José Pablo Galindo Hernández A01276079
//Roberto Carlos Pedraza Miranda A01277764

#include <iostream>
#include <string>
using namespace std;

class CJugador {
public:
    int cantgoles;
    string nombrecompleto;
    string equipo;

    CJugador(int goles, const string& nombre, const string& equipo) {
        cantgoles = goles;
        nombrecompleto = nombre;
        this->equipo = equipo;
    }
};

class CNodo {
private:
    CJugador futbolista;
    CNodo* sig;

public:
    CNodo(const CJugador& f, CNodo* s = NULL) : futbolista(f), sig(s) {}
    friend class CLista;
};
typedef CNodo* pNodo;

class CLista {
private:
    pNodo inicio, actual;

public:
    CLista() { inicio = actual = NULL; }
    ~CLista();
    void Agregar(const CJugador& f);
    void Eliminar(const string& nombre);
    bool ListaVacia() { return inicio == NULL; }
    bool ExisteActual() { return actual != NULL; }
    void Inicio() { actual = inicio; }
    void Siguiente() { if (actual) actual = actual->sig; }
    void Ultimo();
    void Buscarjugador(const int& goal);
    void MostrarLista();
};

CLista::~CLista() {
    actual = inicio;
    while (actual) {
        inicio = inicio->sig;
        delete actual;
        actual = inicio;
    }
}

void CLista::Ultimo() {
    actual = inicio;
    if (!ListaVacia()) {
        while (actual->sig)
            actual = actual->sig;
    }
}

void CLista::MostrarLista() {
    actual = inicio;
    while (actual) {
        cout << "Nombre: " << actual->futbolista.nombrecompleto << ", Equipo: " << actual->futbolista.equipo << ", Goles: " << actual->futbolista.cantgoles << endl;
        actual = actual->sig;
    }
    cout << endl;
}

void CLista::Agregar(const CJugador& f) {
    pNodo anterior;
    if (ListaVacia() || f.cantgoles > inicio->futbolista.cantgoles) {
        inicio = new CNodo(f, inicio);
    } else {
        anterior = inicio;
        while (anterior->sig && f.cantgoles < anterior->sig->futbolista.cantgoles)
            anterior = anterior->sig;

        anterior->sig = new CNodo(f, anterior->sig);
    }
}

void CLista::Eliminar(const string& nombre) {
    pNodo anterior, aux;
    if (ListaVacia()) {
        cout << "No hay nada a eliminar" << endl;
        return;
    }
    aux = inicio;
    anterior = NULL;
    while (aux && aux->futbolista.nombrecompleto < nombre) {
        anterior = aux;
        aux = aux->sig;
    }
    if (!aux || aux->futbolista.nombrecompleto != nombre) {
        cout << "El futbolista no está en la lista" << endl;
        return;
    }
    if (!anterior)
        inicio = inicio->sig;
    else
        anterior->sig = aux->sig;
    delete aux;
}
void CLista::Buscarjugador(const int& goal) {
    actual = inicio;
    while (actual) {
            if (actual->futbolista.cantgoles >= goal) {
                cout << "Jugador encontrado:\n";
                cout << "Nombre: " << actual->futbolista.nombrecompleto << ", Equipo: " << actual->futbolista.equipo << ", Goles: " << actual->futbolista.cantgoles << endl;
            }
            actual = actual->sig;
    }
    cout << "Jugador no encontrado." << endl;
}

int main() {
    CLista milista;
    int opcion;
    string valor;
    int busc;
    int gol;
    string name;
    string team;
    
    milista.Agregar(CJugador(819, "Lionel Messi", "Inter Miami"));
    milista.Agregar(CJugador(855, "Cristiano Ronaldo", "Al-Nassar FC"));
    milista.Agregar(CJugador(805,"Josef Bican","Retirado"));
    milista.Agregar(CJugador(762,"Edson Arantes (Pelé)","Retirado"));
    milista.Agregar(CJugador(755,"Romario de Souza","Retirado"));
    milista.Agregar(CJugador(724,"Ferenc Puskas","Retirado"));
    milista.Agregar(CJugador(648,"Jimmy Jones","Retirado"));
    milista.Agregar(CJugador(634,"Gerd Muller","Retirado"));
    milista.Agregar(CJugador(629,"Joe Bambrick","Retirado"));
    milista.Agregar(CJugador(624,"Abe Lenstra", "Retirado"));
    
        do {
            cout << "Este programa incluye a los 10 maximos goleadores en la historia, ¿Qué quieres hacer? \n";
            cout << "1. Agregar futbolista\n";
            cout << "2. Ver lista\n";
            cout << "3. Eliminar futbolista\n";
            cout << "4. Buscar Jugador\n";
            cout << "5. Salir\n";
          cout << "Ingrese su opcion: ";
            
          cin >> opcion;

            switch (opcion) {
                case 1: {
                    cout << "Ingresa la cantidad de goles: ";
                    cin >> gol;
                    cin.ignore();
                    cout << "Ingresa el nombre completo: ";
                    getline(cin,name);
                    cout << "Ingresa el equipo actual (o pon retirado): ";
                    getline(cin,team);

                    CJugador nuevoFutbolista(gol, name, team);
                    milista.Agregar(nuevoFutbolista);
                    break;
                }
                case 2:
                    cout << "Lista: " << endl;
                    milista.MostrarLista();
                    break;
                case 3: {
                    cin.ignore();
                    cout << "Futbolista a eliminar: ";
                    getline(cin,valor);
                    milista.Eliminar(valor);
                    cout << "Futbolista eliminado" << endl;
                    break;
                }
              case 4: {
                  cout << "Ingrese la cantidad minima de goles que debe tener el jugador a buscar: ";
                  cin>>busc;
                  milista.Buscarjugador(busc);
                  break;
              }
                
                case 5:
                    cout << "Saliendo del programa" << endl;
                    break;
                default:
                    cout << "Opcion invalida" << endl;
                    break;
            }
        } while (opcion != 5);

        return 0;
    }
