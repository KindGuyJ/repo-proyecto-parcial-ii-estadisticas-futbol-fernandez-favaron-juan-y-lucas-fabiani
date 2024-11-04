#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "libreria.h"
using namespace std;


void eliminarRegistro(const string& nombreArchivo, int idEliminar) {
    ifstream archivo(nombreArchivo);
    ofstream temp("temp.csv"); // Archivo temporal
    string linea;
    int idx = 0;

    while (getline(archivo, linea)) {
        if (idx != idEliminar) { // Copia todas las líneas excepto la que queremos eliminar
            temp << linea << endl;
        }
        idx++;
    }

    archivo.close();
    temp.close();
    remove(nombreArchivo.c_str()); // Elimina el archivo original
    rename("temp.csv", nombreArchivo.c_str()); // Renombra el archivo temporal
    cout << "Registro eliminado correctamente." << endl;
}

void modificarRegistro(const string& nombreArchivo, int idModificar, const PARTIDO& nuevoRegistro) {
    ifstream archivo(nombreArchivo);
    ofstream temp("temp.csv"); // Archivo temporal
    string linea;
    int idx = 0;

    while (getline(archivo, linea)) {
        if (idx == idModificar) { // Modifica el registro especificado
            temp << nuevoRegistro.jornada << "," << nuevoRegistro.fecha.toString() << ","
                 << nuevoRegistro.equipolocal << "," << nuevoRegistro.goleslocales << ","
                 << nuevoRegistro.golesvisitantes << "," << nuevoRegistro.equipovisitante << ","
                 << nuevoRegistro.competicion << endl;
        } else {
            temp << linea << endl; // Copia el resto de las líneas sin cambios
        }
        idx++;
    }

    archivo.close();
    temp.close();
    remove(nombreArchivo.c_str()); // Elimina el archivo original
    rename("temp.csv", nombreArchivo.c_str()); // Renombra el archivo temporal
    cout << "Registro modificado correctamente." << endl;
}

void agregarRegistro(const string& nombreArchivo, const PARTIDO& nuevoRegistro) {
    ofstream archivo(nombreArchivo, ios::app); // Abrir en modo de adición
    archivo << nuevoRegistro.jornada << "," << nuevoRegistro.fecha.toString() << ","
            << nuevoRegistro.equipolocal << "," << nuevoRegistro.goleslocales << ","
            << nuevoRegistro.golesvisitantes << "," << nuevoRegistro.equipovisitante << ","
            << nuevoRegistro.competicion << endl;
    archivo.close();
    cout << "Registro agregado correctamente." << endl;
}
