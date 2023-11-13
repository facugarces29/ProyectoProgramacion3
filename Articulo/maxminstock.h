#include <iostream>
#include <sstream>
#include <fstream>
#include "../Articulo/Articulo.h"
#include "../Arbol/ArbolAVL.h"

using namespace std;

//Valor minimo en stock
articulo min_stock(string NombreArchivo, int n) {
    fstream endp;
    endp.open("./" + NombreArchivo, ios::in);

    ArbolBinarioAVL<int> arbol;

    string fila, word;

    while (getline(endp, fila)) {
        int col = 0;
        int stock = 0; //cant stock por artic
        string codigo = " "; //codigo de barras
        string nombre_articulo = " ";

        stringstream s(fila);

        while (getline(s, word, ',')) //pasa por todas las columnas
        {
            if (col == 1) {
                codigo = word;
            }

            if (col == 2) {
                nombre_articulo = word;
            }

            if (col >= 3) {
                int cantidad_art = atoi(word.c_str());  //cant de articulos en entero
                if (cantidad_art >= 1) {
                    stock += cantidad_art;
                }
            }
            col++;
        }

        //articulo new_articulo(nombre_articulo, stock, codigo, " ");

        arbol.put(nombre_articulo, stock);

    arbol.print();
 
}

articulo max_stock(string NombreArchivo, int n) {
    fstream endp;
    endp.open("./" + NombreArchivo, ios::in);

    ArbolBinarioAVL<int> arbol;

    string fila, word;
    int maxStock = 0; // variable para rastrear el máximo stock
    string articuloMaxStock; // variable para almacenar el artículo con el máximo stock

    while (getline(endp, fila)) {
        int col = 0;
        int stock = 0; // cant stock por artículo
        string codigo = " "; // código de barras
        string nombre_articulo = " ";

        stringstream s(fila);

        while (getline(s, word, ',')) // pasa por todas las columnas
        {
            if (col == 1) {
                codigo = word;
            }

            if (col == 2) {
                nombre_articulo = word;
            }

            if (col >= 3) {
                int cantidad_art = atoi(word.c_str());  // cantidad de artículos en entero
                if (cantidad_art >= 1) {
                    stock += cantidad_art;
                }
            }
            col++;
        }

        // Si el stock actual es mayor al máximo conocido, actualiza el máximo y el artículo correspondiente
        if (stock > maxStock) {
            maxStock = stock;
            articuloMaxStock = nombre_articulo;
        }
    }
};