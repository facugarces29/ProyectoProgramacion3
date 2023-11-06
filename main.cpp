#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "ArbolAVL.h" //Supongo que aquí se incluirá el código del árbol AVL
#include "HashMap/HashMap.h"
//1061 articulos
using namespace std;

struct Producto {
    string grupo;
    string codigoBarras;
    string nombre;
    vector<int> depositos;


    // Definimos un operador de comparación para comparar productos por su código de barras
    bool operator<(const Producto& other) const {
        return codigoBarras < other.codigoBarras;
    }

     // Operador de igualdad para comparar productos por igualdad
    bool operator==(const Producto& other) const {
        return codigoBarras == other.codigoBarras;
    }

    // Operador de comparación para comparar productos por ordenamiento (>)
    bool operator>(const Producto& other) const {
        return codigoBarras > other.codigoBarras;
    }
};

vector<vector<string>> leerArchivoCSV(const string& nombreArchivo) {
    vector<vector<string>> datos;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." <<endl;
        return datos;
    }

    string linea, valor;
    getline(archivo, linea); // Ignorar la primera línea


    while (getline(archivo, linea)) {
        vector<string> fila;
        stringstream ss(linea);

        while (getline(ss, valor, ',')) {
            fila.push_back(valor);
        }

        datos.push_back(fila);
    }

    archivo.close();
    return datos;
};



bool esEnteroValido(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
};

int convertir_a_entero(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al convertir a entero: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Desbordamiento de rango. " << e.what() << std::endl;
    }
    return -1;
};

int cantidadTotalArticulos(const vector<vector<string>>& datos) {
    int total = 0;
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4 && esEnteroValido(fila[3])) { 
            try {
                int stock = stoi(fila[3]);
                total += stock;
            } catch (const std::invalid_argument& e) {
                cerr << "Error al convertir a entero en fila: " << e.what() << std::endl;
            }
        } else {
            cerr << "Fila incompleta o el stock no es un número válido." << std::endl;
        }
    }
    return total;
};



int cantidadTotalArticulosDiferentes(const vector<vector<string>>& datos) {
    set<string> codigosBarras;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 2) { // Verificar que hay al menos 2 elementos en la fila (para obtener el código de barras)
            string codigoBarras = fila[1]; // Suponiendo que la columna del código de barras es la segunda (índice 1)
            codigosBarras.insert(codigoBarras);
        }
    }

    return codigosBarras.size();
};


void listarArticulosMinimoStock(const vector<vector<string>>& datos, int minStock) {
    cout << "Artículos con stock igual o menor a " << minStock << ":" << endl;

    HashMap<string, int> stockPorArticulo;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4 && esEnteroValido(fila[3])) {
            string codigoBarras = fila[1];
            int stock = stoi(fila[3]);
            stockPorArticulo[codigoBarras] += stock;
        }
    }

    for (const auto& par : stockPorArticulo) {
        if (par.second <= minStock) {
            cout << "Código: " << par.first << ", Stock: " << par.second << endl;
        }
    }
}
void stockIndividualArticulo(const vector<vector<string>>& datos, const string& nombreArticulo) {
    cout << "Stock individual del artículo '" << nombreArticulo << "':" << endl;

    for (const vector<string>& fila : datos) {
        if (fila[2] == nombreArticulo) { // La columna del nombre del artículo es la tercera (índice 2)
            cout << "Depósito: " << fila[0] << ", Stock: " << fila[3] << endl;
        }
    }
};


void procesarArgumentos(int argc, char* argv[], const vector<vector<string>>& datos) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " [Argumentos] Inventariado_Fisico.csv" << endl;
        return;
    }

    string operacion = argv[1];
    string archivoCSV = argv[2];

    if (operacion == "-total_art_dif") {
        int totalDiferentes = cantidadTotalArticulosDiferentes(datos);
        cout << "Cantidad total de artículos diferentes: " << totalDiferentes << std::endl;
    } else if (operacion == "-total_art") {
        int totalArticulos = cantidadTotalArticulos(datos);
        cout << "Cantidad total de artículos: " << totalArticulos << std::endl;
    } else if (operacion == "-min_stock") {
        if (argc >= 4) {
            int minStock = std::stoi(argv[3]);
            listarArticulosMinimoStock(datos, minStock);
        } else {
            std::cerr << "Falta el valor de stock mínimo." << std::endl;
        }
    } else if (operacion == "-stock") {
        if (argc >= 4) {
            string nombreArticulo = argv[3];
            stockIndividualArticulo(datos, nombreArticulo);
        } else {
            std::cerr << "Falta el nombre del artículo." << std::endl;
        }
    } else {
        std::cerr << "Operación no válida." << std::endl;
    }
};

void mostrarDatosCSV(const vector<vector<string>>& datos) {
    for (const vector<string>& fila : datos) {
        for (const string& valor : fila) {
            cout << valor << ",";
        }
        cout << endl;
    }
};

int main(int argc, char* argv[]) {
    string nombreArchivo = "Inventariado_Fisico.csv";
    vector<vector<string>> datos = leerArchivoCSV(nombreArchivo);

    procesarArgumentos(argc, argv, datos);
    //mostrarDatosCSV(datos);

    return 0;
}

