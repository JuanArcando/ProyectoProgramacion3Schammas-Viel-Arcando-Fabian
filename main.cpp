#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

int totalArticulos, Dep1 = 0, Dep2 = 0, Dep3 = 0, Dep4 = 0;

struct Articulo {
    string grupo;
    string codigo;
    string nombre;
    int deposito1 = 0;
    int deposito2 = 0;
    int deposito3 = 0;
    int deposito4 = 0;
};

class Articulos {
private:
    unordered_map<int, Articulo>& Tabla;

public:
    Articulos(unordered_map<int, Articulo>& t);
    void MostrarDatos();
    void ARTtotalesDIF();
    void ARTtotales();
};

Articulos::Articulos(unordered_map<int, Articulo>& t) : Tabla(t) {
}

void leer(unordered_map<int, Articulo>& tabla) {
    ifstream archivo;
    archivo.open("C:\\Users\\Juan Arcando\\OneDrive\\Escritorio\\ProyectoProgComp\\Tabla.csv", ios::in);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string primeraLinea;
    getline(archivo, primeraLinea);

    string data;
    string Gru, Cod, Nom, Guardar, Deposito1, Deposito2, Deposito3, Deposito4;
    int num = 1, total = 0;
    totalArticulos = 0;

    while (getline(archivo, data)) {
        stringstream stream(data);
        stringstream depo1(Deposito1);
        stringstream depo2(Deposito2);
        stringstream depo3(Deposito3);
        stringstream depo4(Deposito4);

        getline(stream, Gru, ',');
        if (!Gru.empty()) {
            Guardar = Gru;
        }
        getline(stream, Cod, ',');
        getline(stream, Nom, ',');
        getline(stream, Deposito1, ',');
        if (Deposito1.empty()) {
            Deposito1 = "0";
        }
        depo1 >> Dep1;

        getline(stream, Deposito2, ',');
        if (Deposito2.empty()) {
            Deposito2 = "0";
        }
        depo2 >> Dep2;
        getline(stream, Deposito3, ',');
        if (Deposito3.empty()) {
            Deposito3 = "0";
        }
        depo3 >> Dep3;
        getline(stream, Deposito4, ',');
        if (Deposito4.empty()) {
            Deposito4 = "0";
        }
        depo4 >> Dep4;

        tabla[num] = { Guardar, Cod, Nom, Dep1, Dep2, Dep3, Dep4 };
        total = Dep1 + Dep2 + Dep3 + Dep4;
        totalArticulos = total + totalArticulos;
        num++;
    }

    archivo.close();
}

void Articulos::ARTtotalesDIF() {
    cout << "Existen " << Tabla.size() << " artículos diferentes" << endl;
}

void Articulos::ARTtotales() {
    cout << "El total de artículos en todos los depositos es: " << totalArticulos << endl;
}

void Articulos::MostrarDatos() {
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;
        cout << "Numero: " << pair.first << endl;
        cout << "Grupo: " << articulo.grupo << endl;
        cout << "Codigo: " << articulo.codigo << endl;
        cout << "Nombre: " << articulo.nombre << endl;
        cout << "Depositos1:" << articulo.deposito1 << " Depositos2:" << articulo.deposito2 << " Depositos3:" << articulo.deposito3 << " Depositos4:" << articulo.deposito4 << endl;
        cout << "-------------------" << endl;
    }
}

int mostrarMenu() {
    int opcion;
    cout << "Menu:" << endl;
    cout << "1. Mostrar datos de articulos" << endl;
    cout << "2. Mostrar el total de articulos en todos los depositos" << endl;
    cout << "3. Mostrar la cantidad de articulos diferentes" << endl;
    cout << "4. Opcion 4" << endl;
    cout << "5. Opcion 5" << endl;
    cout << "6. Opcion 6" << endl;
    cout << "7. Salir" << endl;
    cout << "Selecciona una opcion: ";
    cin >> opcion;
    return opcion;
}

int main() {
    unordered_map<int, Articulo> tabla;
    leer(tabla);
    Articulos articulos(tabla);

    int opcion;
    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                articulos.MostrarDatos();
                break;
            case 2:
                articulos.ARTtotales();
                break;
            case 3:
                articulos.ARTtotalesDIF();
                break;
            case 4:
                // Agrega la lógica para la opción 4 aquí
                break;
            case 5:
                // Agrega la lógica para la opción 5 aquí
                break;
            case 6:
                // Agrega la lógica para la opción 6 aquí
                break;
            case 7:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, elige una opción válida." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}
