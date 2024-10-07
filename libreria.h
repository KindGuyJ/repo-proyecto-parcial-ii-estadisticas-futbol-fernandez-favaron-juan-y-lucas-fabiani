#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct partido
{
    string Jornada;
    string Fecha;
    string EquipoLocal;
    string GolesLocal;
    string GolesVisitante;
    string EquipoVisitante;
    string Competicion;
};

struct top5 {
    string competiciones[10];
    partido partidos[50];
};

// Capaz cambiar el asignar y get para que den el objeto pero bueno no los use para nada todavia.
class dataclass
{
private:
    vector<partido> data;

public:
    void add(partido s)
    {
        data.push_back(s);
    }
    int size()
    {
        return data.size();
    }
    /// @brief 
    /// @param o A cual de todos los vectores asignar
    /// @param x Nuevo string
    /// @param i [0-6] 0-Jornada; 1-Fecha; 2-EquipoLocal; 3-GolesLocal; 4-GolesVisitante; 5-EquipoVisitante; 6-Competicion;
    void assign(int o, string x, int i)
    {
        switch (i)
        {
        case 0:
            data[o].Jornada = x;
            break;
        case 1:
            data[o].Fecha = x;
            break;
        case 2:
            data[o].EquipoLocal = x;
            break;
        case 3:
            data[o].GolesLocal = x;
            break;
        case 4:
            data[o].GolesVisitante = x;
            break;
        case 5:
            data[o].EquipoVisitante = x;
            break;
        case 6:
            data[o].Competicion = x;
            break;
        default:
            throw 666 - 1;
            break;
        }
    }
    /// @brief 
    /// @param o A cual vector leer
    /// @param i [0-6] 0-Jornada; 1-Fecha; 2-EquipoLocal; 3-GolesLocal; 4-GolesVisitante; 5-EquipoVisitante; 6-Competicion;
    /// @return la data
    string get(int o, int i)
    {
        switch (i)
        {
        case 0:
            return data[o].Jornada;
            break;
        case 1:
            return data[o].Fecha;
            break;
        case 2:
            return data[o].EquipoLocal;
            break;
        case 3:
            return data[o].GolesLocal;
            break;
        case 4:
            return data[o].GolesVisitante;
            break;
        case 5:
            return data[o].EquipoVisitante;
            break;
        case 6:
            return data[o].Competicion;
            break;
        default:
            throw 666 - 2;
            break;
        }
    }
    partido* last(){
        return &(*data.end());
    }

};