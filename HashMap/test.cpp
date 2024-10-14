#include <iostream>
#include <string>
#include "HashMap.h" // Asegúrate de que las rutas estén correctas
#include "HashEntry.h" 

int main() {
    // Crear un HashMap con tamaño 10 y la función de hash predeterminada
    HashMap<int, std::string> miMapa(10);

    // Insertar valores
    miMapa.put(1, "Uno");
    miMapa.put(2, "Dos");
    miMapa.put(3, "Tres");

    // Obtener valores
    try {
        std::cout << "Valor asociado a la clave 1: " << miMapa.get(1) << std::endl;
        std::cout << "Valor asociado a la clave 2: " << miMapa.get(2) << std::endl;
        std::cout << "Valor asociado a la clave 3: " << miMapa.get(3) << std::endl;
    } catch (int e) {
        std::cerr << "Error: Clave no encontrada." << std::endl;
    }

    // Imprimir el contenido del mapa
    miMapa.print();

    return 0;
}