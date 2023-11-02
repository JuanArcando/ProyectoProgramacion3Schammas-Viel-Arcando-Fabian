#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

struct Articulo {
    string grupo;
    string codigo;
    string nombre;
    string deposito1;
    string deposito2;
    string deposito3;
    string deposito4;
};

class Articulos {
private:
    unordered_map<int, Articulo>& Tabla;

public:
    Articulos(unordered_map<int, Articulo>& t);
    void Agregar(const string&, const string&, const string&, const string&, const string&, const string&, const string&);
    void MostrarDatos();
};

Articulos::Articulos(unordered_map<int, Articulo>& t) : Tabla(t) {
}

void Articulos::Agregar(const string& Grupo, const string& Codigo, const string& Nombre, const string& Deposito1, const string& Deposito2, const string& Deposito3, const string& Deposito4) {
    Articulo articulo;
    articulo.grupo = Grupo;
    articulo.codigo = Codigo;
    articulo.nombre = Nombre;
    articulo.deposito1 = Deposito1;
    articulo.deposito2 = Deposito2;
    articulo.deposito3 = Deposito3;
    articulo.deposito4 = Deposito4;
}

void Articulos::MostrarDatos() {
    for (int numero = 1; numero <= Tabla.size(); numero++) {
        if (Tabla.find(numero) != Tabla.end()) {
            const Articulo& articulo = Tabla[numero];
            cout << "Numero: " << numero << endl;
            cout << "Grupo: " << articulo.grupo << endl;
            cout << "Codigo: " << articulo.codigo << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Depositos (1,2,3,4,5): " << articulo.deposito1 << endl;
            cout << "-------------------" << endl;
        }
    }
}

void leer(unordered_map<int, Articulo>& tabla) {
    ifstream archivo;
    archivo.open("C:\\Users\\Juan Arcando\\OneDrive\\Escritorio\\ProyectoProgComp\\Tabla.csv", ios::in);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    // Leer y descartar la primera línea
    string primeraLinea;
    getline(archivo, primeraLinea);

    string data;
    string Gru, Cod, Nom, Guardar;
    int num = 1;

    while (getline(archivo, data)) {
        stringstream stream(data);
        getline(stream, Gru, ',');
        if (!Gru.empty()) {
            Guardar = Gru;
        }
        getline(stream, Cod, ',');
        getline(stream, Nom, ',');

        string Deposito1, Deposito2, Deposito3, Deposito4;
        for (int i = 1; i <= 4; i++) {
            if (!stream.good()) {
                break;
            }
            string Deposito;
            stream >> Deposito;
            if (!stream.fail()) {
                if (i == 1) {
                    Deposito1 = Deposito;
                }
                else if (i == 2) {
                    Deposito2 = Deposito;
                }
                else if (i == 3) {
                    Deposito3 = Deposito;
                }
                else if (i == 4) {
                    Deposito4 = Deposito;
                }
            }
        }
        // Luego de obtener los valores, puedes agregarlos a la tabla
        tabla[num] = { Guardar, Cod, Nom, Deposito1, Deposito2, Deposito3, Deposito4 };
        num++;
    }

    archivo.close();
}


int main() {
    unordered_map<int, Articulo> tabla;
    leer(tabla);
    Articulos articulos(tabla);
    articulos.MostrarDatos();
    return 0;
}