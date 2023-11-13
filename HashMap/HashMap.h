#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_

#include "HashEntry.h"
#include <functional>

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

    T get(K clave) const;

    void put(K clave, T valor) const;

    void remove(K clave);

    ~HashMap();

    bool esVacio() const;

    void print() const;
};

template <class K, class T>
HashMap<K, T>::HashMap(unsigned int k)
{
    tamanio = k;
    tabla = new HashEntry<K, T> *[tamanio];
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
    tabla = new HashEntry<K, T> *[tamanio];
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
}

template <class K, class T>
T HashMap<K, T>::get(K clave) const
{
    unsigned int pos = hashFuncP(clave) % tamanio;
    if (tabla[pos] == nullptr)
    {
        throw 404;
    }
    if (tabla[pos]->getClave() == clave)
    {
        return tabla[pos]->getValor();
    }
    else
    {
        throw 409;
    }
}

template <class K, class T>
void HashMap<K, T>::put(K clave, T valor) const
{
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] != nullptr)
    {
        //Manejar la Colision!!!!!!!
        throw 409;
    }

    tabla[pos] = new HashEntry<K, T>(clave, valor); //Corresponde a una fila en la tabla HASH
}

template <class K, class T>
void HashMap<K, T>::remove(K clave) {}

template <class K, class T>
bool HashMap<K, T>::esVacio() const
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
    // Implementa una función de hash adecuada para tus claves
    // Esta es solo una implementación de ejemplo, debes ajustarla según tus necesidades
    std::hash<K> hashFunction;
    return hashFunction(clave);
}

template <class K, class T>
void HashMap<K, T>::print() const
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
            const auto &valor = tabla[i]->getValor();
            if constexpr (std::is_same<T, std::vector<int>>::value)
            {
                for (const auto &elem : valor)
                {
                    std::cout << elem << " ";
                }
            }
            else
            {
                std::cout << valor;
            }
        }
        std::cout << std::endl;
    }
}

#endif // U05_HASH_HASHMAP_HASHMAP_H_
