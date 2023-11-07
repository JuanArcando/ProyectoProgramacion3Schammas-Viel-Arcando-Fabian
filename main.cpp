#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

int totalArticulos, Dep1 = 0, Dep2 = 0, Dep3 = 0, Dep4 = 0, Dep5 = 0;

struct Articulo {
    string grupo;
    string codigo;
    string nombre;
    int deposito1 = 0;
    int deposito2 = 0;
    int deposito3 = 0;
    int deposito4 = 0;
    int deposito5 = 0;
};

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
    string Gru, Cod, Nom, Guardar, Deposito1, Deposito2, Deposito3, Deposito4, Deposito5;
    int num = 1, total = 0;
    totalArticulos = 0;

    while (getline(archivo, data)) {
        stringstream stream(data);

        getline(stream, Gru, ',');
        if (!Gru.empty()) {
            Guardar = Gru;
        }
        getline(stream, Cod, ',');
        getline(stream, Nom, ',');

        stringstream depo1, depo2, depo3, depo4, depo5;
        getline(stream, Deposito1, ',');
        if (Deposito1.empty()) {
            Deposito1 = "0";
        }
        depo1 << Deposito1;

        getline(stream, Deposito2, ',');
        if (Deposito2.empty()) {
            Deposito2 = "0";
        }
        depo2 << Deposito2;

        getline(stream, Deposito3, ',');
        if (Deposito3.empty()) {
            Deposito3 = "0";
        }
        depo3 << Deposito3;

        getline(stream, Deposito4, ',');
        if (Deposito4.empty()) {
            Deposito4 = "0";
        }
        depo4 << Deposito4;

        getline(stream, Deposito5, ',');
        if (Deposito5.empty()) {
            Deposito5 = "0";
        }
        depo5 << Deposito5;

        depo1 >> Dep1;
        depo2 >> Dep2;
        depo3 >> Dep3;
        depo4 >> Dep4;
        depo5 >> Dep5;

        total = Dep1 + Dep2 + Dep3 + Dep4 + Dep5;
        totalArticulos = total + totalArticulos;

        tabla[num] = { Guardar, Cod, Nom, Dep1, Dep2, Dep3, Dep4, Dep5 };
        num++;
    }


    archivo.close();
}

void Articulos::ARTtotalesDIF() {
    cout << "Existen " << Tabla.size() << " articulos diferentes" << endl;
}

void Articulos::ARTtotales() {
    cout << "El total de articulos en todos los depositos es: " << totalArticulos << endl;
}

void Articulos::MostrarDatos() {
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;
        cout << "Numero: " << pair.first << endl;
        cout << "Grupo: " << articulo.grupo << endl;
        cout << "Codigo: " << articulo.codigo << endl;
        cout << "Nombre: " << articulo.nombre << endl;
        cout << "Depositos1: " << articulo.deposito1 << " Depositos2: " << articulo.deposito2 << " Depositos3: " << articulo.deposito3 << " Depositos4: " << articulo.deposito4 << " Depositos5: " << articulo.deposito5 << endl;
        cout << "-------------------" << endl;
    }
}

void MostrarArticulosMenorIgualN(const unordered_map<int, Articulo>& tabla, int n) {
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = articulo.deposito1 + articulo.deposito2 + articulo.deposito3 + articulo.deposito4 + articulo.deposito5;
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
        cout << "No hay articulos con un stock menor o igual a " << n << endl;
    }
    else {
        cout << "Total de articulos con stock menor o igual a " << n << ": " << cantidadArticulos << endl;
    }
}

void max_Stock(const unordered_map<int, Articulo>& tabla, int mayor) {
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = articulo.deposito1 + articulo.deposito2 + articulo.deposito3 + articulo.deposito4 + articulo.deposito5;

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
        cout << "No hay articulos con un stock igual o superior a " << mayor << endl;
    }
    else {
        cout << "Total de articulos con stock igual o superior a " << mayor << ": " << cantidadArticulos << endl;
    }
}

void Articulos::StockNombre() {
    bool encontrado = false;
    string nombre;
    cin.ignore();
    cout << "Ingrese el nombre del producto cuyo stock desea conocer (Ingreselo en MAYUSCULAS, ejemplo: 'GRIFERIA VASSER ALIZE EXT  PARED 2 LLAVES 24/2310'): ";
    getline(cin, nombre);
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;

            cout << "Numero: " << pair.first << endl;
            cout << "Grupo: " << articulo.grupo << endl;
            cout << "Codigo: " << articulo.codigo << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Stock en Deposito 1: " << articulo.deposito1 << endl;
            cout << "Stock en Deposito 2: " << articulo.deposito2 << endl;
            cout << "Stock en Deposito 3: " << articulo.deposito3 << endl;
            cout << "Stock en Deposito 4: " << articulo.deposito4 << endl;
            cout << "Stock en Deposito 5: " << articulo.deposito5 << endl;
            cout << "-------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron articulos con el nombre '" << nombre << "'." << endl;
    }
}

void Articulos::StockNomYDep() {
    bool encontrado = false;
    string nombre;
    cin.ignore();
    int NumDep = 0;
    cout << "Ingrese el nombre del producto: ";
    getline(cin, nombre);

    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;
            cout << "Ingrese el numero de deposito (1, 2, 3, 4 o 5): ";
            cin >> NumDep;

            switch (NumDep) {
                case 1:
                    cout << "La cantidad de objetos encontrados en el deposito " << NumDep << " es: ";
                    cout << articulo.deposito1 << endl;
                    break;
                case 2:
                    cout << "La cantidad de objetos encontrados en el deposito " << NumDep << " es: ";
                    cout << articulo.deposito2 << endl;
                    break;
                case 3:
                    cout << "La cantidad de objetos encontrados en el deposito " << NumDep << " es: ";
                    cout << articulo.deposito3 << endl;
                    break;
                case 4:
                    cout << "La cantidad de objetos encontrados en el deposito " << NumDep << " es: ";
                    cout << articulo.deposito4 << endl;
                    break;
                case 5:
                    cout << "La cantidad de objetos encontrados en el deposito " << NumDep << " es: ";
                    cout << articulo.deposito5 << endl;
                    break;
                default:
                    cout << "Ingrese un valor de deposito valido (1, 2, 3, 4 o 5)." << endl;
                    break;
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron articulos con el nombre '" << nombre << "'." << endl;

    }
    return;
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
    cout << "7. Ver stock por deposito de un articulo en particular" << endl;
    cout << "8. Salir del programa" << endl;
    cout << "9. Tutorial" << endl;
    cout << "Selecciona una opcion: ";
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
                cout << "Ingrese el valor de n: ";
                cin >> n;
                MostrarArticulosMenorIgualN(tabla, n);
                break;
            case 5:
                int mayor;
                cout << "Ingrese el valor de n: ";
                cin >> mayor;
                max_Stock(tabla, mayor);
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
                cout << "Bienvenido! A continuacion le mostraremos una breve explicacion de nuestro proyecto: " <<endl;
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