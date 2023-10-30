#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../Parcial_2/ArbolAVL.h" // Supongo que aquí se incluirá el código del árbol AVL

struct Producto {
    std::string grupo;
    std::string codigoBarras;
    std::string nombre;
    int depositos[5];

    // Definimos un operador de comparación para comparar productos por su código de barras
    bool operator<(const Producto& other) const {
        return codigoBarras < other.codigoBarras;
    }
};

int main() {
    // Crear el árbol AVL
    ArbolBinarioAVL<Producto> arbol;

    // Nombre del archivo CSV
    std::string archivoCSV = "tu_archivo.csv";

    // Abrir el archivo
    std::ifstream archivo(archivoCSV);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo CSV." << std::endl;
        return 1;
    }

    // Variables para almacenar los datos del archivo
    std::string linea;
    char delimitador = ',';

    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string grupo, codigoBarras, nombre;
        int depositos[5]; // Ajusta el tamaño según tus necesidades

        // Leer datos usando el delimitador ","
        std::getline(ss, grupo, delimitador);
        ss >> codigoBarras;
        ss.ignore(); // Ignorar la coma
        std::getline(ss, nombre, delimitador);

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
