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

Articulo::Articulo() {
}

class Articulos {
private:
    unordered_map<int, Articulo>& Tabla;

public:
    Articulos(unordered_map<int, Articulo>& t);
    string MostrarDatos();
    string ARTtotalesDIF();
    string ARTtotales();
    string StockNombre();
    string StockNomYDep();
    void StockNomDepU(ofstream& archivoSalida);
};

Articulos::Articulos(unordered_map<int, Articulo>& t) : Tabla(t) {
}

string Articulos::ARTtotalesDIF() {
    stringstream result;
    result << "Existen " << Tabla.size() << " articulos diferentes";
    return result.str();
}

string Articulos::ARTtotales() {
    stringstream result;
    result << "La cantidad de articulos totales es: " << totalArticulos;
    return result.str();
}

string Articulos::MostrarDatos() {
    stringstream result;
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;
        result << "Numero: " << pair.first << endl;
        result << "Grupo: " << articulo.grupo << endl;
        result << "Codigo: " << articulo.codigo << endl;
        result << "Nombre: " << articulo.nombre << endl;
        result << "Depositos: ";
        for (int deposito : articulo.depositos) {
            result << deposito << " ";
        }
        result << endl;
        result << "-------------------" << endl;
    }
    return result.str();
}

string Articulos::StockNombre() {
    stringstream result;
    bool encontrado = false;
    string nombre;
    cin.ignore();
    result << "Ingrese el nombre del producto cuyo stock desea conocer: ";
    getline(cin, nombre);
    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;

            result << "Numero: " << pair.first << endl;
            result << "Grupo: " << articulo.grupo << endl;
            result << "Codigo: " << articulo.codigo << endl;
            result << "Nombre: " << articulo.nombre << endl;
            result << "Stock en Depositos: ";
            for (int deposito : articulo.depositos) {
                result << deposito << " ";
            }
            result << endl;
            result << "-------------------" << endl;
        }
    }

    if (!encontrado) {
        result << "No se encontraron articulos con el nombre '" << nombre << "'.";
    }

    return result.str();
}

string Articulos::StockNomYDep() {
    stringstream result;
    bool encontrado = false;
    string nombre;
    cin.ignore();
    result << "Ingrese el nombre del producto: ";
    getline(cin, nombre);

    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.nombre == nombre) {
            encontrado = true;
            int dep, i = 0;
            result << "Ingrese el deposito que desea revisar el stock (los depositos van de 0 a x ): ";
            cin >> dep;
            result << "Numero de deposito\tStock" << endl;
            bool encontrarDEP = false;
            while (i < articulo.depositos.size()) {
                if (i == dep) {
                    result << i + 1 << "\t\t" << articulo.depositos[i] << endl;
                    encontrarDEP = true;
                    break;
                } else {
                    i++;
                }
            }
            if (!encontrarDEP) {
                result << "No se encontro el deposito " << dep;
            }
        }
    }
    return result.str();
}

string MostrarArticulosMenorIgualN(const unordered_map<int, Articulo>& tabla, int n) {
    stringstream result;
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = 0;
        for (int stock : articulo.depositos) {
            totalStock += stock;
        }
        if (totalStock <= n) {
            result << "Numero: " << pair.first << endl;
            result << "Grupo: " << articulo.grupo << endl;
            result << "Codigo: " << articulo.codigo << endl;
            result << "Nombre: " << articulo.nombre << endl;
            result << "Total de stock: " << totalStock << endl;
            result << "-------------------" << endl;
            cantidadArticulos++;
        }
    }

    if (cantidadArticulos == 0) {
        result << "No hay articulos con un stock menor o igual a " << n;
    } else {
        result << "Total de articulos con stock menor o igual a " << n << ": " << cantidadArticulos;
    }

    return result.str();
}

string max_Stock(const unordered_map<int, Articulo>& tabla, int mayor) {
    stringstream result;
    int cantidadArticulos = 0;

    for (const auto& pair : tabla) {
        const Articulo& articulo = pair.second;
        int totalStock = 0;
        for (int stock : articulo.depositos) {
            totalStock += stock;
        }

        if (totalStock >= mayor) {
            result << "Numero: " << pair.first << endl;
            result << "Grupo: " << articulo.grupo << endl;
            result << "Codigo: " << articulo.codigo << endl;
            result << "Nombre: " << articulo.nombre << endl;
            result << "Total de stock: " << totalStock << endl;
            result << "-------------------" << endl;
            cantidadArticulos++;
        }
    }

    if (cantidadArticulos == 0) {
        result << "No hay articulos con un stock igual o superior a " << mayor;
    } else {
        result << "Total de articulos con stock igual o superior a " << mayor << ": " << cantidadArticulos;
    }

    return result.str();
}

void Articulos::StockNomDepU(ofstream& archivoSalida) {
    int dep;
    cout << "Ingrese el numero de deposito que quiere buscar los datos: ";
    cin >> dep;

    int cantidad;
    cout << "Ingrese la cantidad de objetos de referencia: ";
    cin >> cantidad;

    bool encontrado = false;

    for (const auto& pair : Tabla) {
        const Articulo& articulo = pair.second;

        if (articulo.depositos.size() > dep) {
            int stockDeposito = articulo.depositos[dep];

            if (stockDeposito <= cantidad) {
                archivoSalida << "Numero: " << pair.first << endl;
                archivoSalida << "Grupo: " << articulo.grupo << endl;
                archivoSalida << "Codigo: " << articulo.codigo << endl;
                archivoSalida << "Nombre: " << articulo.nombre << endl;
                archivoSalida << "Stock en deposito " << dep << ": " << stockDeposito << endl;
                archivoSalida << "-------------------" << endl;

                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        archivoSalida << "No se encontraron articulos en el deposito " << dep << " con stock menor o igual a " << cantidad << "." << endl;
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
            } else {
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

int obtenerNumeroUsuario() {
    int numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    return numero;
}

int mostrarMenu() {
    int opcion;
    cout << "Menu:" << endl;
    cout << "1. Mostrar datos de articulos" << endl;
    cout << "2. Mostrar el total de articulos en todos los depositos" << endl;
    cout << "3. Mostrar la cantidad de articulos diferentes" << endl;
    cout << "4. Listado de articulos con cantidad n o menos de stock" << endl;
    cout << "5. Listado de aquellos articulos cuyo stock es igual o supera el numero n." << endl;
    cout << "6. Busqueda de articulo y stock por nombre (depositos van de 0 a x)" << endl;
    cout << "7. Ver stock por deposito de un articulo en particular (Escribir en MAYUSCULAS el nombre del producto (PILETA C. CERART PARIS GRANDE  BCA  P/)" << endl;
    cout << "8. Salir del programa" << endl;
    cout << "9. Tutorial" << endl;
    cout << "10. Busqueda de articulos en un deposito con stock menor o igual a una cantidad de referencia" << endl;
    cout << "Selecciona una opcion: ";
    cin >> opcion;
    return opcion;
}

int main() {
    ofstream archivoSalida("Procesador_inventario.txt", ios::app);

    unordered_map<int, Articulo> tabla;
    leer(tabla);
    Articulos articulos(tabla);

    int opcion = 0;
    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                archivoSalida << articulos.MostrarDatos() << endl;
                break;
            case 2:
                archivoSalida << articulos.ARTtotales() << endl;
                break;
            case 3:
                archivoSalida << articulos.ARTtotalesDIF() << endl;
                break;
            case 4:
                archivoSalida << MostrarArticulosMenorIgualN(tabla, obtenerNumeroUsuario()) << endl;
                break;
            case 5:
                archivoSalida << max_Stock(tabla, obtenerNumeroUsuario()) << endl;
                break;
            case 6:
                archivoSalida << articulos.StockNombre() << endl;
                break;
            case 7:
                archivoSalida << articulos.StockNomYDep() << endl;
                break;
            case 8:
                cout << "Saliendo del programa." << endl;
                break;
            case 9:
                archivoSalida << "Tutorial: " << endl;
                archivoSalida << "Bienvenido! Nosotros somos ATS Systems!" << endl;
                archivoSalida << "---------------------------------------" << endl;
                archivoSalida << "A continuacion le explicaremos como funciona nuestro programa "<< endl;
                archivoSalida << "Usted primero debe ingresar el numero de opcion que desea utilizar" << endl;
                archivoSalida << "Despues de ingresar la opcion deseada, en caso de ser necesario, el programa le pedira algunos datos extras para mostrarle la infromacion que usted necesita"<<endl;
                archivoSalida << "En las opciones 6 y 7 usted debe ingresar el nombre EXACTO del producto" << endl;
                archivoSalida << "Los depositos van de 0 a x (x segun la cantidad de depositos que USTED necesita)" << endl;
                archivoSalida << "Todas las respuestas son almacenadas y enviadas a el archivo 'Procesador_Inventario.txt' donde usted las puede ver mas comodamente" <<endl;\
                archivoSalida << " Gracias por confiar en ATS Systems "<<endl;
                break;
            case 10:
                articulos.StockNomDepU(archivoSalida);
                break;
            default:
                archivoSalida << "Opcion no valida. Por favor, elija una opcion valida." << endl;
                break;
        }
    } while (opcion != 8);

    archivoSalida.close();
    return 0;
}
