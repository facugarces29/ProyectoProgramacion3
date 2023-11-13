#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Lista/Lista.h"

template <class T>
Lista<T> min_stock(int n, const Nodo<T>* inicio) {
    Lista<T> resultado;
    const Nodo<T>* aux = inicio;

    while (aux != nullptr) {
        try {
            // Convertir el valor a entero e insertarlo en la lista
            int valor = std::stoi(aux->getDato());
            if (valor <= n) {
                resultado.insertarUltimo(std::to_string(valor));

            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error al convertir el valor a entero: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Valor fuera de rango: " << e.what() << std::endl;
        }
        aux = aux->getSiguiente();
    }

    return resultado;
}


int main() {
    // Crear una instancia de la Lista
    Lista<std::string> miLista;  // Cambiar a std::string para manejar cualquier tipo de dato

    // Leer desde el archivo CSV
    std::ifstream archivo("prueba.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string dato;

            // Suponiendo que cada línea del archivo contiene un solo valor (cantidad de stock)
            while (std::getline(ss, dato, ',')) {
                // Insertar el valor en la lista
                miLista.insertarUltimo(dato);
            }
        }
        archivo.close();

        // Llamar a la función min_stock con n = 5
        Lista<std::string> resultado = min_stock(5, miLista.getInicio());

        // Imprimir la lista resultante
        resultado.print();
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    return 0;
}