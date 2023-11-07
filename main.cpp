#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int totalArticulos;

struct Articulo {
    Articulo();
    string grupo;
    string codigo;
    string nombre;
    vector<int> depositos;
};
Articulo::Articulo()
{
}

class Articulos {
private:
    unordered_map<int, Articulo>& Tabla;

public:
    Articulos(unordered_map<int, Articulo>& t);
    void MostrarDatos();
    void ARTtotalesDIF();
    void ARTtotales();
    void StockNombre();
    void StockNomYDep();
};

Articulos::Articulos(unordered_map<int, Articulo>& t) : Tabla(t) {
}


void Articulos::ARTtotalesDIF() {
    cout << "Existen " << Tabla.size() << " articulos diferentes" << endl;
}

void Articulos::ARTtotales() {
    cout << "La cantidad de articulos totales es: " << totalArticulos << endl;
}

void Articulos::MostrarDatos() {
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;
        cout << "Numero: " << pair.first << endl;
        cout << "Grupo: " << articulo.grupo << endl;
        cout << "Codigo: " << articulo.codigo << endl;
        cout << "Nombre: " << articulo.nombre << endl;
        cout << "Depositos: ";
        for (int deposito : articulo.depositos) {
            cout << deposito << " ";
        }
        cout << endl;
        cout << "-------------------" << endl;
    }
}

void Articulos::StockNombre() {
    bool encontrado = false;
    string nombre;
    cin.ignore();
    cout << "Ingrese el nombre del producto cuyo stock desea conocer: ";
    getline(cin, nombre);
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;

            cout << "Numero: " << pair.first << endl;
            cout << "Grupo: " << articulo.grupo << endl;
            cout << "Código: " << articulo.codigo << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Stock en Depositos: ";
            for (int deposito : articulo.depositos) {
                cout << deposito << " ";
            }
            cout << endl;
            cout << "-------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron artículos con el nombre '" << nombre << "'." << endl;
    }
}

void Articulos::StockNomYDep() {
    bool encontrado = false;
    string nombre;
    cin.ignore();
    cout << "Ingrese el nombre del producto: ";
    getline(cin, nombre);

    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;
            int dep,i=0;
            cout << "Ingrese el deposito que desea revisar el stock: "; cin >> dep;
            cout << "Numero de deposito\tStock" << endl;
            bool encontrarDEP = false;
            while (i < articulo.depositos.size()) {
                if (i == dep) {
                    cout << i + 1 << "\t\t" << articulo.depositos[i] << endl;
                    encontrarDEP = true;
                    break;
                }
                else {
                    i++;
                }
            }
            if (!encontrarDEP) {
                cout << "No se encontro el deposito "<<dep<<endl;
            }
        }
    }
}

void MostrarArticulosMenorIgualN(const unordered_map<int, Articulo>& tabla, int n) {
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = 0;
        for (int stock : articulo.depositos) {
            totalStock += stock;
        }
        if (totalStock <= n) {
            cout << "Numero: " << pair.first << endl;
            cout << "Grupo: " << articulo.grupo << endl;
            cout << "Codigo: " << articulo.codigo << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Total de stock: " << totalStock << endl;
            cout << "-------------------" << endl;
            cantidadArticulos++;
        }
    }

    if (cantidadArticulos == 0) {
        cout << "No hay artículos con un stock menor o igual a " << n << endl;
    }
    else {
        cout << "Total de artículos con stock menor o igual a " << n << ": " << cantidadArticulos << endl;
    }
}

void max_Stock(const unordered_map<int, Articulo>& tabla, int mayor) {
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = 0;
        for (int stock : articulo.depositos) {
            totalStock += stock;
        }

        if (totalStock >= mayor) {
            cout << "Numero: " << pair.first << endl;
            cout << "Grupo: " << articulo.grupo << endl;
            cout << "Codigo: " << articulo.codigo << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Total de stock: " << totalStock << endl;
            cout << "-------------------" << endl;
            cantidadArticulos++;
        }
    }

    if (cantidadArticulos == 0) {
        cout << "No hay artículos con un stock igual o superior a " << mayor << endl;
    }
    else {
        cout << "Total de artículos con stock igual o superior a " << mayor << ": " << cantidadArticulos << endl;
    }
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
    string Gru, Cod, Nom;
    int num = 1;
    totalArticulos = 0;

    while (getline(archivo, data)) {
        stringstream stream(data);

        getline(stream, Gru, ',');
        getline(stream, Cod, ',');
        getline(stream, Nom, ',');

        Articulo articulo;
        tabla[num] = articulo;

        string depositoStr;
        stringstream dep;
        int deposito;

        while (getline(stream, depositoStr, ',')) {
            if (!depositoStr.empty()) {

                dep << depositoStr;
                dep >> deposito;
                totalArticulos = deposito + totalArticulos;
                tabla[num].depositos.push_back(deposito);
            }
            else {
                tabla[num].depositos.push_back(0);
            }
        }

        tabla[num].grupo = Gru;
        tabla[num].codigo = Cod;
        tabla[num].nombre = Nom;
        num++;
    }

    archivo.close();
}


int mostrarMenu() {
    int opcion;
    cout << "Menu:" << endl;
    cout << "1. Mostrar datos de articulos" << endl;
    cout << "2. Mostrar el total de articulos en todos los depositos" << endl;
    cout << "3. Mostrar la cantidad de articulos diferentes" << endl;
    cout << "4. Listado de articulos con cantidad n o menos de stock" << endl;
    cout << "5. Listado de aquellos articulos cuyo stock es igual o supera el numero n." << endl;
    cout << "6. Busqueda de articulo y stock por nombre" << endl;
    cout << "7. Ver stock por deposito de un articulo en particular (Escribir en MAYUSCULAS el nombre del producto (PILETA C. CERART PARIS GRANDE  BCA  P/)" << endl;
    cout << "8. Salir del programa" << endl;
    cout << "9. Tutorial" << endl;
    cout << "Selecciona una opcio: ";
    cin >> opcion;
    return opcion;
}

int main() {
    unordered_map<int, Articulo> tabla;
    leer(tabla);
    Articulos articulos(tabla);

    int opcion = 0;
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
                int n;
                cout << "Ingrese la cantidad a comparar en el stock: "; cin >> n;
                MostrarArticulosMenorIgualN(tabla, n);
                break;
            case 5:
                int x;
                cout << "Ingrese la cantidad a comparar en el stock: "; cin >> x;
                max_Stock(tabla, x);
                break;
            case 6:
                articulos.StockNombre();
                break;
            case 7:
                articulos.StockNomYDep();
                break;
            case 8:
                cout << "Saliendo del programa." << endl;
                break;
            case 9:
                cout << "Tutorial: " << endl;
                cout << "Bienvenido! A continuacion le mostraremos una breve explicacion de nuestro proyecto: " << endl;
                cout << "Usted primero debe ingresar el nUmero de opcion que desea utilizar" << endl;
                cout << "En las opciones 6 y 7 usted debe ingresar el nombre EXACTO del producto" << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, elija una opcion valida." << endl;
                break;
        }
    } while (opcion != 8);

    return 0;
}