#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> //para stream


using namespace std;

struct Date {
    int dia, mes, year;

    Date(const string& s) {
        sscanf(s.c_str(), "%d/%d/%d", &dia, &mes, &year);
    }

    Date(){
        dia=0;mes=0;year=0;
    }

    bool operator>(const Date& other) const {
        if (year != other.year) return year > other.year;
        if (mes != other.mes) return mes > other.mes;
        return dia > other.dia;
    }

    bool operator<(const Date& other) const { //totalmente innecesario
        if (year != other.year) return year < other.year;
        if (mes != other.mes) return mes < other.mes;
        return dia < other.dia;
    }
    
    bool operator==(const Date& other) const {
        if (year == other.year && mes == other.mes && dia > other.dia) return true;
        else return false;
    }

    //Conversor a string
    std::string toString() const {
        std::ostringstream oss;
        oss << dia << "/" << mes << "/" << year;
        return oss.str();
    }
};

struct partido
{
    string Jornada="";
    Date Fecha;
    string EquipoLocal="";
    int GolesLocal=0;
    int GolesVisitante=0;
    string EquipoVisitante="";
    string Competicion="";
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
            data[o].GolesLocal = stoi(x);
            break;
        case 4:
            data[o].GolesVisitante = stoi(x);
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
            return data[o].Fecha.toString();
            break;
        case 2:
            return data[o].EquipoLocal;
            break;
        case 3:
            return to_string(data[o].GolesLocal);
            break;
        case 4:
            return to_string(data[o].GolesVisitante);
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
    // Devuelve un puntero a equipo
    partido* last(){
        if (data.empty()) throw 66;
        return &data.back();
    }

};