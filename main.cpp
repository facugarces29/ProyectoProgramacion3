#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "ArbolAVL.h" //Supongo que aquí se incluirá el código del árbol AVL

using namespace std;

struct Producto {
    string grupo;
    string codigoBarras;
    string nombre;
    int depositos[5];

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
}

int cantidadTotalArticulos(const vector<vector<string>>& datos) {
    return datos.size();
}

int cantidadTotalArticulosDiferentes(const vector<vector<string>>& datos) {
    set<string> codigosBarras;

    for (const vector<string>& fila : datos) {
        string codigoBarras = fila[1]; // Suponiendo que la columna del código de barras es la segunda (índice 1)
        codigosBarras.insert(codigoBarras);
    }

    return codigosBarras.size();
}

void listarArticulosMinimoStock(const vector<vector<string>>& datos, int minStock) {
    cout << "Artículos con stock igual o menor a " << minStock << ":" << endl;

    for (const vector<string>& fila : datos) {
        int stock = stoi(fila[3]); // La cantidad de stock está en la cuarta columna (índice 3)
        
        if (stock <= minStock) {
            cout << "Código: " << fila[1] << ", Nombre: " << fila[2] << ", Stock: " << stock << endl;
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
}
void procesarArgumentos(int argc, char* argv[], const vector<vector<string>>& datos) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " [Argumentos] inventariofisico.csv" << endl;
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
}
int main(int argc, char* argv[]) {
    string nombreArchivo = "Inventariado_Fisico.csv";
    vector<vector<string>> datos = leerArchivoCSV(nombreArchivo);

    procesarArgumentos(argc, argv, datos);

    return 0;
}

/*
int main() {
    // Crear el árbol AVL
    ArbolBinarioAVL<Producto> arbol;

    // Nombre del archivo CSV
    string archivoCSV = "Inventariado_Fisico.csv";

    // Abrir el archivo
    ifstream archivo(archivoCSV);

   if (!archivo.is_open()) {
        cout << "Error al abrir el archivo CSV." << endl;
        return 1;
    }

    // Variables para almacenar los datos del archivo
    string linea;
    char delimitador = ',';

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string grupo, codigoBarras, nombre;
        int depositos[5]; // Ajusta el tamaño según tus necesidades

        // Leer datos usando el delimitador ","
        getline(ss, grupo, delimitador);
        ss >> codigoBarras;
        ss.ignore(); // Ignorar la coma
        getline(ss, nombre, delimitador);

        for (int i = 0; i < 5; i++) {
            ss >> depositos[i];
            ss.ignore(); // Ignorar la coma
        }

        // Crear un producto con los datos leídos
        Producto producto = {grupo, codigoBarras, nombre};
        for (int i = 0; i < 5; i++) {
            producto.depositos[i] = depositos[i];
        }

        // Insertar el producto en el árbol AVL
        arbol.put(producto);
    }

    // Aquí puedes realizar otras operaciones con el árbol AVL

    // Cerrar el archivo
    archivo.close();

    return 0;
}
*/