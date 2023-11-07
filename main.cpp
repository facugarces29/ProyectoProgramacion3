#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "ArbolAVL.h" // Supongo que aquí se incluirá el código del árbol AVL

using namespace std;

struct Producto {
    string grupo;
    string codigoBarras;
    string nombre;
    vector<int> depositos;

    bool operator<(const Producto& other) const {
        return codigoBarras < other.codigoBarras;
    }

    bool operator==(const Producto& other) const {
        return codigoBarras == other.codigoBarras;
    }

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

int cantidadTotalArticulosDiferentes(const vector<vector<string>>& datos) {
    set<string> codigosBarras;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 2) { // Verificar que haya al menos 2 elementos en la fila (para obtener el código de barras)
            string codigoBarras = fila[1]; // Suponiendo que la columna del código de barras es la segunda (índice 1)
            codigosBarras.insert(codigoBarras);
        }
    }

    return codigosBarras.size();
};

void listarArticulosMinimoStock(const vector<vector<string>>& datos, int minStock, ArbolBinarioAVL<Producto>& miArbol) {
    cout << "Artículos con stock igual o menor a " << minStock << ":" << endl;

    // Recorrer los datos del archivo CSV
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4) { // Asegurarse de que haya al menos 4 elementos en la fila (columnas necesarias)
            string codigoBarras = fila[1];
            if (esEnteroValido(fila[3])) { // Verificar que el stock sea un número válido
                int stock = stoi(fila[3]);

                // Crear un objeto Producto y agregarlo al árbol AVL
                Producto nuevoProducto;
                nuevoProducto.codigoBarras = codigoBarras;
                nuevoProducto.nombre = fila[2]; // Suponiendo que la columna 2 contiene el nombre del producto
                nuevoProducto.depositos = {convertir_a_entero(fila[0])}; // Suponiendo que la columna 0 contiene el depósito

                miArbol.put(nuevoProducto);
            }
        }
    }
}

void stockIndividualArticulo(const vector<vector<string>>& datos, const string& nombreArticulo) {
    cout << "Stock individual del artículo '" << nombreArticulo << "':" << endl;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4) {
            if (fila[2] == nombreArticulo) { // La columna del nombre del artículo es la tercera (índice 2)
                cout << "Depósito: " << fila[0] << ", Stock: " << fila[3] << endl;
            }
        }
    }
}

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
        // Total de artículos ya se calcula en la función principal, no es necesario repetirlo aquí.
        cerr << "Operación no válida." << std::endl;
    } else if (operacion == "-min_stock") {
        if (argc >= 4) {
            int minStock = std::stoi(argv[3]);
            ArbolBinarioAVL<Producto> miArbol;
            listarArticulosMinimoStock(datos, minStock, miArbol);
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
}

int main(int argc, char* argv[]) {
    string nombreArchivo = "../Inventariado_Fisico.csv";
    vector<vector<string>> datos = leerArchivoCSV(nombreArchivo);

    // Procesar argumentos
    procesarArgumentos(argc, argv, datos);

    return 0;
}

