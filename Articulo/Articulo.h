#include <iostream>
#include "../Lista/Lista.h"

using namespace std;

class articulo {
    string nombre;
    int stock; // que sea un objeto de la clase stock.
    string codigo;
    string grupo;

public:

    articulo(){}
    articulo(string nom, int stoc, string code, string grup){
        nombre = nom;
        stock = stoc;
        codigo = code;
        grupo = grup;

    }

    void setNom(string nom){
        nombre = nom;
    }
    string getNom(){
        return nombre;
    }

    void setStock(int stoc){
        stock = stoc;
    }

    int getStock(){
        return stock;
    }

    void setCode(char code){
        codigo = code;
    }

    string getCode(){
        return codigo;
    }

    void setGrup(string grup){
        grupo = grup;
    }

    string getGrup(){
        return grupo;
    }

    void imprimir(){
        cout<< "Nombre: "<<nombre<<endl;
        cout<< "Codigo: "<<codigo<<endl;
        cout<< "Stock: "<< stock<<endl;
    }


    ~articulo() = default;

    friend std::ostream& operator<<(std::ostream& os, const articulo& a) {
        os << "Nombre: " << a.nombre << ", Codigo: " << a.codigo << ", Stock: " << a.stock;
        return os;
    }
};