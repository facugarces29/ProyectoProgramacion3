#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
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
void reemplazarCaracteres(string& str) {
    replace(str.begin(), str.end(), '/', ' ');
    replace(str.begin(), str.end(), '-', ' ');
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
        // Reemplazar '/' y '-' en la línea
        replace(linea.begin(), linea.end(), '/', ' ');
        replace(linea.begin(), linea.end(), '-', ' ');
        replace(linea.begin(), linea.end(), '.',' ');

        // Verificar si la línea contiene la palabra "error"
        if (linea.find("error"||"ERROR") != string::npos) {
            continue; // Si contiene "error", se salta la línea
        }

        vector<string> fila;
        stringstream ss(linea);

        while (getline(ss, valor, ',')) {
            // Reemplazar celdas vacías con "null"
            if (valor.empty()) {
                valor = "null";
            }
            fila.push_back(valor);
        }

        datos.push_back(fila);
    }

    archivo.close();
    return datos;
}


bool esEnteroValido(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int convertir_a_entero(const string& str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Error al convertir a entero: " << e.what() << endl;
    } catch (const out_of_range& e) {
        cerr << "Error: Desbordamiento de rango. " << e.what() << endl;
    }
    return -1;
};

int cantidadTotalArticulos(const vector<vector<string>>& datos) {
    int total = 0;
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 5) { 
            for (int i = 3; i <= 7; ++i) {
                if (!fila[i].empty() && esEnteroValido(fila[i])) { 
                    int stock = convertir_a_entero(fila[i]); 
                    if (stock != -1) {
                        total += stock;
                    }
                }
            }
        } else {
            cerr << "Fila incompleta, no se pudo contar el stock." << endl;
        }
    }
    return total;
}
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
                nuevoProducto.depositos = {convertir_a_entero(fila[3])}; // Suponiendo que la columna 3 contiene el depósito

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


// -stock [nombre_articulo], [deposito] 
void stockDepositoArticulo(const vector<vector<string>>& datos, const string& nombreArticulo, int deposito) {
    cout << "Stock del artículo '" << nombreArticulo << "' en el depósito " << deposito << ":" << endl;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4) {
            if (fila[2] == nombreArticulo && esEnteroValido(fila[0])) {
                int dep = convertir_a_entero(fila[0]);
                if (dep == deposito) {
                    cout << "Depósito: " << fila[0] << ", Stock: " << fila[3] << endl;
                }
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
        int totalArticulos = cantidadTotalArticulos(datos);
        cout << "Cantidad total de artículos: " << totalArticulos << std::endl;
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
    string nombreArchivo = "Inventariado_Fisico.csv";
    vector<vector<string>> datos = leerArchivoCSV(nombreArchivo);

    // Procesar argumentos
    procesarArgumentos(argc, argv, datos);
    //mostrarDatosCSV(datos);
    return 0;
}

