#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_

#include "MiEntradaHash.h"

template <class K, class T>
class HashMap
{
private:
  HashEntry<K, T> **tabla;
  unsigned int tamanio;

  unsigned int hashFunc(K clave);
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
  unsigned int espacioRestante();
  T* buscar(const K& clave);
};

template <class K, class T>
HashMap<K, T>::HashMap(unsigned int k)
{
  tamanio = k;
  tabla = new HashEntry<K, T> *[tamanio];
  for (int i = 0; i < tamanio; i++)
  {
    tabla[i] = NULL;
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
    tabla[i] = NULL;
  }
  hashFuncP = fp;
}

template <class K, class T>
HashMap<K, T>::~HashMap()
{
  for (int i = 0; i < tamanio; i++)
  {
    if (tabla[i] != NULL)
    {
      delete tabla[i];
    }
  }
}

template <class K, class T>
T HashMap<K, T>::get(K clave)
{
    unsigned int pos = hashFuncP(clave) % tamanio;
    unsigned int originalPos = pos;

    while (tabla[pos] != NULL)
    {
        if (tabla[pos]->getClave() == clave)
        {
            return tabla[pos]->getValor();
        }
        pos = (pos + 1) % tamanio;
        if (pos == originalPos) // Si regresamos al inicio
        {
            break; // La clave no existe
        }
    }
    throw 404;
}

template <class K, class T>
void HashMap<K, T>::put(K clave, T valor)
{
  unsigned int pos = hashFuncP(clave) % tamanio;
  unsigned int originalPos = pos;

  while (tabla[pos] != NULL)
  {
    if (tabla[pos]->getClave() == clave)
    {
      tabla[pos]->setValor(valor); // Si la clave ya existe, actualiza el valor
      return;
    }
    pos = (pos + 1) % tamanio; // Open Hashing por si se repite la clave (muy probable)
    if (pos == originalPos)
    {
      throw std::overflow_error("Se lleno el hash????");
    }
  }

  tabla[pos] = new HashEntry<K, T>(clave, valor);
}

template <class K, class T>
void HashMap<K, T>::remove(K clave) {}

template <class K, class T>
bool HashMap<K, T>::esVacio()
{
  for (int i = 0; i < tamanio; i++)
  {
    if (tabla[i] != NULL)
    {
      return false;
    }
  }
  return true;
}

template <class K, class T>
unsigned int HashMap<K, T>::*hashFunc(K clave)
{
  return hashFuncP(clave);
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
    if (tabla[i] != NULL)
    {
      std::cout << tabla[i]->getClave() << "\t\t";
      std::cout << tabla[i]->getValor();
    }
    std::cout << std::endl;
  }
}

template <class K, class T>
unsigned int HashMap<K, T>::espacioRestante()
{
  unsigned int x=0;
  for (int i = 0; i < tamanio; i++)
  {
    if (tabla[i] != NULL)
    {
      x++;
    }
  }
  return x;
}

template <class K, class T>
T* HashMap<K, T>::buscar(const K& clave) {
    unsigned int pos = hashFuncP(clave) % tamanio; 
    unsigned int originalPos = pos; //Por si damos toda la vuelta
    bool noinicial = false;

    while (tabla[pos] != NULL) { //Con una tabla grande no deberiamos perder mucho tiempo con openhashing
        if (tabla[pos]->getClave() == clave) {
            return &(tabla[pos]->getValorReal());
        }
        pos = (pos + 1) % tamanio;

        if (pos == originalPos && noinicial) {
            break;
        }
        noinicial = true;
    }
    return nullptr;
}
#endif // U05_HASH_HASHMAP_HASHMAP_H_
