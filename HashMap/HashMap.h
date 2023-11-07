#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_

#include <string>
#include "../HashMap/HashEntry.h"

template <class K, class T>
class HashMap
{
private:
    HashEntry<K, T> **tabla;
    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

public:
    explicit HashMap(unsigned int k);

    HashMap(unsigned int k, unsigned int (*hashFuncP)(K clave));

    T get(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMap();

    bool esVacio();

    void print();
};

template <class K, class T>
HashMap<K, T>::HashMap(unsigned int k)
{
    tamanio = k;
    tabla = new HashEntry<K, T> *[tamanio]();
    for (int i = 0; i < tamanio; i++)
    {
        tabla[i] = nullptr;
    }
    hashFuncP = hashFunc;
}

template <class K, class T>
HashMap<K, T>::HashMap(unsigned int k, unsigned int (*fp)(K))
{
    tamanio = k;
    tabla = new HashEntry<K, T> *[tamanio]();
    for (int i = 0; i < tamanio; i++)
    {
        tabla[i] = nullptr;
    }
    hashFuncP = fp;
}

template <class K, class T>
HashMap<K, T>::~HashMap()
{
    for (int i = 0; i < tamanio; i++)
    {
        if (tabla[i] != nullptr)
        {
            delete tabla[i];
        }
    }
    delete[] tabla;
}

template <class K, class T>
T HashMap<K, T>::get(K clave)
{
    unsigned int pos = hashFuncP(clave) % tamanio;
    if (tabla[pos] == nullptr)
    {
        throw 404; // Puedes definir un tipo de excepción más descriptivo
    }
    if (tabla[pos]->getClave() == clave)
    {
        return tabla[pos]->getValor();
    }
    else
    {
        throw 409; // Puedes definir un tipo de excepción más descriptivo
    }
}

template <class K, class T>
void HashMap<K, T>::put(K clave, T valor)
{
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] != nullptr)
    {
        // Manejar la Colisión aquí
        throw 409; // Puedes definir un tipo de excepción más descriptivo
    }

    tabla[pos] = new HashEntry<K, T>(clave, valor); // Corresponde a una fila en la tabla HASH
}

template <class K, class T>
void HashMap<K, T>::remove(K clave)
{
    unsigned int pos = hashFuncP(clave) % tamanio;
    if (tabla[pos] != nullptr)
    {
        delete tabla[pos];
        tabla[pos] = nullptr;
    }
}

template <class K, class T>
bool HashMap<K, T>::esVacio()
{
    for (int i = 0; i < tamanio; i++)
    {
        if (tabla[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

template <class K, class T>
unsigned int HashMap<K, T>::hashFunc(K clave)
{
    // Puedes implementar una función hash adecuada aquí para claves de tipo std::string.
    // Esta implementación de hash simple convierte la clave en un valor sin firmar.
    return static_cast<unsigned int>(clave);
}

template <class K, class T>
void HashMap<K, T>::print()
{
    std::cout << "i"
              << " "
              << "Clave"
              << "\t\t"
              << "Valor" << std::endl;
    std::cout << "--------------------" << std::endl;
    for (int i = 0; i < tamanio; i++)
    {
        std::cout << i << " ";
        if (tabla[i] != nullptr)
        {
            std::cout << tabla[i]->getClave() << "\t\t";
            std::cout << tabla[i]->getValor();
        }
        std::cout << std::endl;
    }
}

#endif // U05_HASH_HASHMAP_HASHMAP_H_

