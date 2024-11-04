#ifndef HASH_MAP
#define HASH_MAP

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

template <typename KeyType, typename ValueType>
class HashMap {
private:
    // Usaremos una lista de pares para manejar colisiones (encadenamiento)
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t capacity; // Tamaño de la tabla
    size_t size;     // Número de elementos en el mapa

    // Función hash simple
    size_t hash(const KeyType& key) const {
        return std::hash<KeyType>()(key) % capacity;
    }

public:
    HashMap(size_t cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Método para insertar o actualizar el valor asociado a la clave
    void operator[](const KeyType& key, const ValueType& value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Actualiza el valor si la clave ya existe
                return;
            }
        }
        table[index].emplace_back(key, value); // Inserta nuevo par clave-valor
        ++size;
    }

    // Método para obtener el valor asociado a una clave
    ValueType get(const KeyType& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second; // Retorna el valor si se encuentra la clave
            }
        }
        throw std::runtime_error("Key not found"); // Excepción si no se encuentra la clave
    }

    // Método para eliminar un elemento por clave
    void remove(const KeyType& key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        auto it = std::find_if(bucket.begin(), bucket.end(), [&key](const std::pair<KeyType, ValueType>& pair) {
            return pair.first == key;
        });

        if (it != bucket.end()) {
            bucket.erase(it); // Elimina el par clave-valor
            --size;
        }
    }

    // Método para verificar si el mapa está vacío
    bool empty() const {
        return size == 0;
    }

    // Método para verificar si una clave existe
    bool has(const KeyType& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true; // Retorna true si la clave existe
            }
        }
        return false; // Retorna false si la clave no se encuentra
    }

    // Método para obtener todas las claves
    std::vector<KeyType> keys() const {
        std::vector<KeyType> keysList;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                keysList.push_back(pair.first); // Agrega la clave a la lista
            }
        }
        return keysList; // Retorna la lista de claves
    }

    // Método para obtener el tamaño actual del HashMap
    size_t getSize() const {
        return size;
    }
};


#endif