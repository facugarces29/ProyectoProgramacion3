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
    string grupo;                           // Operadores de comparación para poder ordenar
    string codigoBarras;                    // y comparar productos.
    string nombre;
    vector<int> depositos;
    // Operadores de comparación para poder ordenar
    // y comparar productos.

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

// Esta función lee un archivo CSV y devuelve una matriz de cadenas 'datos
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

//Funcion para validar los enteros
bool esEnteroValido(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
//cConvierte los string al int
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


//Muestra la cantidad de articulos totales
//-total_art
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

//Muestra la cantidad Diferentes de articulos
//-total_art_dif
int cantidadTotalArticulosDiferentes(const vector<vector<string>>& datos) {
    set<string> codigosBarras;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 3) { // Verificar que haya al menos 3 elementos en la fila (para obtener el código de barras)
            string codigoBarras = fila[1]; // Suponiendo que la columna del código de barras es la segunda (índice 1)
            codigosBarras.insert(codigoBarras);
        }
    }

    return codigosBarras.size();
};


//Listar articulos min
//-min_stock
void MinStock(const vector<vector<string>>& datos, int n) {
    ArbolBinarioAVL<string> arbol;

    for (const vector<string>& fila : datos) {
        if (fila.size() >= 3) {
            string nombreArticulo = fila[2]; // Suponiendo que la columna del nombre del artículo es la tercera (índice 2)
            int stock = convertir_a_entero(fila[5]); // Suponiendo que la columna del stock es la sexta (índice 5)
            if (stock != -1) {
                arbol.put(nombreArticulo);
            }
        }
    }

    arbol.inorder(); // Esto imprimirá los artículos en orden (puedes modificarlo para mostrarlos de la forma que necesites)
}

// Función para obtener el stock del artículo en un depósito.
void stockDepositoArticulo(const vector<vector<string>>& datos, const string& nombreArticulo, int deposito) {
    cout << "Stock del artículo '" << nombreArticulo << "' en el depósito " << deposito << ":" << endl;
    int stockDeposito = 0;
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 2) {
            if (fila[2] == nombreArticulo && fila.size() >= 4 && esEnteroValido(fila[3])) {
                int stock = convertir_a_entero(fila[3]);
                if (stock != -1) {
                    vector<int> depositos;
                    istringstream ss(fila[4]);
                    string depositoStr;
                    while (getline(ss, depositoStr, '|')) {
                        depositos.push_back(convertir_a_entero(depositoStr));
                    }
                    if (find(depositos.begin(), depositos.end(), deposito) != depositos.end()) {
                        cout << "Nombre: " << fila[2] << ", Stock: " << stock << endl;
                    }
                }
            }
        }
    }
}

// Función para listar artículos cuyo stock es igual o supera el número n.
void listarArticulosMaxStock(const vector<vector<string>>& datos, int maxStock) {
    cout << "Artículos con stock igual o superior a " << maxStock << ":" << endl;
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4 && esEnteroValido(fila[3])) {
            int stock = convertir_a_entero(fila[3]);
            if (stock != -1 && stock >= maxStock) {
                cout << "Nombre: " << fila[2] << ", Stock: " << stock << endl;
            }
        }
    }
}

// Función para listar artículos con cantidad n o menos de stock según un depósito y nombre de artículo.
void listarArticulosMinimoStockDeposito(const vector<vector<string>>& datos, const string& nombreArticulo, int n, int deposito) {
    cout << "Artículos con stock igual o menor a " << n << " en el depósito " << deposito << " para el artículo '" << nombreArticulo << "':" << endl;
    for (const vector<string>& fila : datos) {
        if (fila.size() >= 4 && esEnteroValido(fila[3]) && fila.size() >= 2) {
            int stock = convertir_a_entero(fila[3]);
            if (stock != -1) {
                vector<int> depositos;
                istringstream ss(fila[4]);
                string depositoStr;
                while (getline(ss, depositoStr, '|')) {
                    depositos.push_back(convertir_a_entero(depositoStr));
                }
                // Comparar el nombre con el miembro 'nombre' de la estructura Producto
                if (stock <= n && find(depositos.begin(), depositos.end(), deposito) != depositos.end() && nombreArticulo == fila[2]) {
                    cout << "Nombre: " << fila[2] << ", Stock: " << stock << endl;
                }
            }
        }
    }
}


//procesa los argumentos que son ingresados por consola y los redirije hacia la funcion que sea solicitada
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
        if (argc >= 4 && esEnteroValido(argv[3])) {
            int n = convertir_a_entero(argv[3]);
            MinStock(datos, n);
        } else {
            cerr << "Argumento inválido para -min_stock." << endl;
        }
    } else if (operacion == "-Stock_Deposito") {
        if (argc >= 5) {
            string nombreArticulo = argv[3];
            if (esEnteroValido(argv[4])) {
                int deposito = convertir_a_entero(argv[4]);
                stockDepositoArticulo(datos, nombreArticulo, deposito);
            } else {
                cerr << "Argumento inválido para número de depósito." << endl;
            }
        } else {
            cerr << "Faltan argumentos para -Stock_Deposito." << endl;
        }
    } else if (operacion == "-listar_max_stock") {
        if (argc >= 4 && esEnteroValido(argv[3])) {
            int maxStock = convertir_a_entero(argv[3]);
            listarArticulosMaxStock(datos, maxStock);
        } else {
            cerr << "Argumento inválido para -listar_max_stock." << endl;
        }
    } else if (operacion == "-listar_min_stock_dep") {
        if (argc >= 5) {
            string nombreArticulo = argv[3];
            if (argc >= 6 && esEnteroValido(argv[4])) {
                int n = convertir_a_entero(argv[4]);
                if (esEnteroValido(argv[5])) {
                    int deposito = convertir_a_entero(argv[5]);
                    listarArticulosMinimoStockDeposito(datos, nombreArticulo, n, deposito);
                } else {
                    cerr << "Argumento inválido para número de depósito." << endl;
                }
            } else {
                cerr << "Argumento inválido para cantidad mínima de stock." << endl;
            }
        } else {
            cerr << "Faltan argumentos para -listar_min_stock_dep." << endl;
        }
    } else {
        std::cerr << "Operación no válida." << std::endl;
    }
}
//Funcion para poder chequear los datos del .csv
void mostrarDatosCSV(const vector<vector<string>>& datos) {
    for (const vector<string>& fila : datos) {
        for (const string& valor : fila) {
            cout << valor << ",";
        }
        cout << endl;
    }
}
//Programa principal
int main(int argc, char* argv[]) {
    string nombreArchivo = "Inventariado_Fisico.csv";
    vector<vector<string>> datos = leerArchivoCSV(nombreArchivo);

    // Procesar argumentos
    procesarArgumentos(argc, argv, datos);
    //Funcion para comprobar los datos del archivo.csv  
    //mostrarDatosCSV(datos);
    return 0;
}

