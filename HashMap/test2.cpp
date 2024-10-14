#include <iostream>
#include <string>
#include "HashMap.h"
#include "HashEntry.h"

// Definir la función de hash
unsigned int customHashFunc(std::string clave) {
    unsigned int hash = 0;
    for (char c : clave) {
        hash = hash * 37 + static_cast<unsigned int>(c);
    }
    return hash;
}

int main() {
    // Crear un HashMap con tamaño 1000 y una función de hash personalizada para std::string
    HashMap<std::string, int> golesporcompetencia(1000, customHashFunc);

    // Insertar valores
    golesporcompetencia.put("Torneo A", 20);
    golesporcompetencia.put("Torneo B", 15);
    golesporcompetencia.put("Torneo C", 30);

    // Obtener valores
    try {
        std::cout << "Goles en 'Torneo A': " << golesporcompetencia.get("Torneo A") << std::endl;
        std::cout << "Goles en 'Torneo B': " << golesporcompetencia.get("Torneo B") << std::endl;
        std::cout << "Goles en 'Torneo C': " << golesporcompetencia.get("Torneo C") << std::endl;
    } catch (int e) {
        std::cerr << "Error: Clave no encontrada." << std::endl;
    }

    // Imprimir el contenido del mapa
    golesporcompetencia.print();

    return 0;
}
