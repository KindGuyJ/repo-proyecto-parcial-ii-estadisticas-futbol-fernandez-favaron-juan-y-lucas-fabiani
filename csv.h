#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "libreria.h"
using namespace std;

const string archivoOg = "Base_Datos_COMA.csv";

void eliminarRegistro(int idEliminar) {
    ifstream archivo(archivoOg);
    ofstream temp("temp.csv"); // Archivo temporal
    string linea;
    int idx = -1;

    while (getline(archivo, linea)) {
        if (idx != idEliminar) { // Copia todas las líneas excepto la que queremos eliminar
            temp << linea << endl;
        }
        idx++;
    }

    archivo.close();
    temp.close();
    remove(archivoOg.c_str()); // Elimina el archivo original
    rename("temp.csv", archivoOg.c_str()); // Renombra el archivo temporal
    cout << "Registro eliminado correctamente." << endl;
}

void modificarRegistro(int idModificar, const Partido& nuevoRegistro) {
    ifstream archivo(archivoOg);
    ofstream temp("temp.csv"); // Archivo temporal
    string linea;
    int idx = -1;

    while (getline(archivo, linea)) {
        if (idx == idModificar) { // Modifica el registro especificado
            temp << nuevoRegistro.jornada << "," << nuevoRegistro.fecha.toString() << ","
                 << nuevoRegistro.equipoLocal << "," << nuevoRegistro.golesLocal << ","
                 << nuevoRegistro.golesVisita << "," << nuevoRegistro.equipoVisita << ","
                 << nuevoRegistro.competicion << endl;
        } else {
            temp << linea << endl; // Copia el resto de las líneas sin cambios
        }
        idx++;
    }

    archivo.close();
    temp.close();
    remove(archivoOg.c_str()); // Elimina el archivo original
    rename("temp.csv", archivoOg.c_str()); // Renombra el archivo temporal
    cout << "Registro modificado correctamente." << endl;
}

void agregarRegistro(const Partido& nuevoRegistro) {
    ofstream archivo(archivoOg, ios::app); // Abrir en modo de adición
    archivo << nuevoRegistro.jornada << "," << nuevoRegistro.fecha.toString() << ","
            << nuevoRegistro.equipoLocal << "," << nuevoRegistro.golesLocal << ","
            << nuevoRegistro.golesVisita << "," << nuevoRegistro.equipoVisita << ","
            << nuevoRegistro.competicion << endl;
    archivo.close();
    cout << "Registro agregado correctamente." << endl;
}
