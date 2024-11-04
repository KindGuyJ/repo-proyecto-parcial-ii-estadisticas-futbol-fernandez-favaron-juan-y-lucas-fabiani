#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <iostream>
#include <vector> //Lista optimizada
#include <fstream>
#include <sstream> //para stream
#include <iomanip> //para setw
#include <unordered_set>
#include "MiHash.h" //OpenHashing

using namespace std;

// Funcion de hash basada en FNV-1
unsigned int customHashFunc(string clave)
{
    const unsigned int FNV_PRIME = 16777619u;
    const unsigned int OFFSET_BASIS = 2166136261u;

    unsigned int hash = OFFSET_BASIS;
    for (char competencia : clave)
    {
        hash = hash * FNV_PRIME;
        hash = hash ^ static_cast<unsigned int>(competencia);
    }
    return hash;
}

// Struct que representa una fecha, puede crease a partir de un string "DD/MM/AAAA"
struct FECHA
{
    int dia, mes, year;

    FECHA(const string &s)
    {
        sscanf(s.c_str(), "%d/%d/%d", &dia, &mes, &year);
    }

    FECHA()
    {
        dia = 0;
        mes = 0;
        year = 0;
    }

    bool operator>(const FECHA &other) const
    {
        if (year != other.year)
            return year > other.year;
        if (mes != other.mes)
            return mes > other.mes;
        return dia > other.dia;
    }

    bool operator<(const FECHA &other) const
    { // totalmente innecesario
        if (year != other.year)
            return year < other.year;
        if (mes != other.mes)
            return mes < other.mes;
        return dia < other.dia;
    }

    bool operator==(const FECHA &other) const
    {
        if (year == other.year && mes == other.mes && dia > other.dia)
            return true;
        else
            return false;
    }

    // Conversor a string
    std::string toString() const
    {
        std::ostringstream oss;
        oss << dia << "/" << mes << "/" << year;
        return oss.str();
    }
};

// Struct para guardar cada partido ingresado de manera eficiente
struct Partido
{
    string jornada = "";
    FECHA fecha;
    string equipolocal = "";
    int goleslocales = 0;
    int golesvisitantes = 0;
    string equipovisitante = "";
    string competicion = "";

    static void printHeaders()
    {
        cout << setw(20) << "Jornada"
             << setw(15) << "Fecha"
             << setw(20) << "Equipo Local"
             << setw(10) << "Goles"
             << setw(20) << "Equipo Visitante"
             << endl
             << setfill('-') << setw(70) << "" << setfill(' ') << endl;
    }

    void printRow() const
    {
        cout << setw(20) << right << jornada
             << setw(15) << right << fecha.toString()
             << setw(20) << right << equipolocal
             << setw(4) << right << goleslocales
             << setw(2) << "  "
             << setw(4) << left << golesvisitantes
             << setw(20) << left << equipovisitante << "\n";
    }
};

struct MEJORES_PARTIDOS
{
    int goals = 0;
    Partido partidos[5];
    string mejorequipo;
    string peorequipo;

    // Movido como funcion del struct pero puede ser una funcion aparte idealmente.
    void print(string competencia)
    {
        cout << endl
             << "Competicion: " << competencia << endl
             << "Goles convertidos en la competencia: " << goals << endl
             << "Mejor equipo por goles convertidos: " << mejorequipo << endl
             << "Peor equipo por goles convertidos: " << peorequipo << endl
             << endl;

        Partido::printHeaders();

        for (const Partido &partido : partidos)
            partido.printRow();
    }

    void mejor(Partido x)
    {
        for (int i = 0; i < 5; i++)
        {
            if ((x.goleslocales + x.golesvisitantes) > (partidos[i].goleslocales + partidos[i].golesvisitantes))
            {
                Partido t = partidos[i];
                partidos[i] = x;
                for (int j = i + 1; j < 5; j++)
                {
                    x = partidos[j];
                    partidos[j] = t;
                    t = x;
                }
                return;
            }
        }
        // si los 5 partidos tienen los mismos goles se ejecuta esto, que no es lindo pero simple
        if ((x.goleslocales + x.golesvisitantes) == (partidos[0].goleslocales + partidos[0].golesvisitantes))
        {
            // Ordeno los 5 que ya estaban por FECHA
            for (int i = 0; i < 5; i++)
            {
                for (int j = 1; j < 5; j++)
                {
                    if ((partidos[i].fecha) < (partidos[j].fecha))
                    {
                        Partido t = partidos[i];
                        partidos[i] = partidos[j];
                        partidos[j] = t;
                    }
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if ((x.fecha) > (partidos[i].fecha))
                {
                    Partido t = partidos[i];
                    partidos[i] = x;
                    for (int j = i + 1; j < 5; j++)
                    {
                        x = partidos[j];
                        partidos[j] = t;
                        t = x;
                    }
                    return;
                }
            }
        }
    }
};

// Struct para guardar los mejores partidos de una competición.
struct ESTADISTICAS_EQUIPO
{
    int win = 0;
    int lost = 0;
    int goles = 0;
    int cgoles = 0;         // goles de los oponentes
    int fechas[2] = {0, 0}; //[0] es Mejor y [1] es Peor
    int partidos = 0;
    FECHA mejor_fecha;
    FECHA peor_fecha;
    vector<int> lista;

    void print()
    {
        cout << "Victorias: " << win << endl;
        cout << "Derrotas: " << lost << endl;
        cout << "Goles a favor: " << goles << endl;
        cout << "Goles del oponente: " << cgoles << endl;
        cout << "Goles a favor en promedio: " << promedioGoles() << endl;
        cout << "Goles del oponente en promedio: " << static_cast<float>(cgoles) / partidos << endl;
        cout << "Mejor fecha: " << mejor_fecha.toString() << endl;
        cout << "Peor fecha: " << peor_fecha.toString() << endl;
        cout << "Partidos: " << partidos << endl;
    }

    float promedioGoles()
    {
        return static_cast<float>(goles) / partidos;
    }
};

// Clase que calcula las estadisticas de tantos partidos se manden a la funcion Ingresar(), a su vez guarda los nombres de los equipos y competencias
class Estadisticas
{
private:
    unordered_set<string> competiciones;
    unordered_set<string> equipos;
    HashMap<std::string, MEJORES_PARTIDOS> Estadisticascompetencias;
    HashMap<std::string, ESTADISTICAS_EQUIPO> EstadisticasTodosLosEquipos;
    //[0] mejor competicion por cantidad de goles, [1] equipo con mas goles, [2] equipo con menos goles
    string Absoluto[3];

public:
    Estadisticas();
    ~Estadisticas();
    void Ingresar(Partido &p, const int &pp);      // Se puede usar para cargar el Partido desde cupholder
    void print(string equipo, string competencia); // No es final, solo debugging
    void llenado();
    void Calculofinal();
    void MejorYPeorEquipo();
    vector<int> getPartidosPor(string equipo, string competencia);
    void printcompetencia(string competencia);
    void printtodascompetencias();
    void MasGolesCompeticion();
    bool EquipoyCompetenciaExiste(string hash);
    unordered_set<string> CualesCompetencias();
    void printEstadisticasEquipos(int umbral, bool esMax);
    void Goles(string equipo, string competencia);
};

void Estadisticas::printEstadisticasEquipos(int umbral, bool esMax)
{
    for (const auto &competencia : competiciones)
    {
        for (const auto &equipo : equipos)
        {
            ESTADISTICAS_EQUIPO *px = EstadisticasTodosLosEquipos.buscar(equipo + competencia);
            if (px != nullptr)
            {
                if ((esMax && px->promedioGoles() < umbral) ||
                    (!esMax && px->promedioGoles() > umbral))
                {
                    cout << equipo << " ,goles promedio: " << px->promedioGoles() << " en la competencia: " << competencia<<endl;
                }
            }
        }
    }
}

Estadisticas::Estadisticas() : Estadisticascompetencias(10, customHashFunc), EstadisticasTodosLosEquipos(400, customHashFunc)
{
}
Estadisticas::~Estadisticas() {
};

unordered_set<string> Estadisticas::CualesCompetencias()
{
    return competiciones;
}

void Estadisticas::Calculofinal()
{

    // Logica para peor y mejor equipo por cantidad de goles, mejorable...
    string mejor, peor;
    int cmejor = 0, cpeor = 1000, cgoles = 0;

    // Mejores partidos por competencia
    for (const auto &competencia : competiciones)
    {
        cmejor = 0, cpeor = 1000;
        for (const auto &equipo : equipos)
        {
            ESTADISTICAS_EQUIPO *px = EstadisticasTodosLosEquipos.buscar(equipo + competencia);
            if (px != nullptr)
            {
                ESTADISTICAS_EQUIPO x = *px;
                if (cpeor > x.goles)
                {
                    cpeor = x.goles;
                    peor = equipo;
                }
                if (cmejor < x.goles)
                {
                    cmejor = x.goles;
                    mejor = equipo;
                }
            }
        }
        MEJORES_PARTIDOS *y = Estadisticascompetencias.buscar(competencia);
        y->mejorequipo = mejor;
        y->peorequipo = peor;
        // Competencia con mas goles:
        if (cgoles < y->goals)
        {
            Absoluto[0] = competencia;
            cgoles = y->goals;
        }

        // Equipo con mas y menos goles de todas las competencias
        int co = 0;
        cmejor = 0;
        cpeor = 1000;
        for (const auto &e : equipos)
        {
            co = 0;
            for (const auto &c : competiciones)
            {
                ESTADISTICAS_EQUIPO *px = EstadisticasTodosLosEquipos.buscar(e + c);
                if (px != nullptr)
                {
                    co += px->goles;
                }
            }
            if (co < cpeor)
            {
                cpeor = co;
                Absoluto[2] = e;
            }
            if (co > cmejor)
            {
                cmejor = co;
                Absoluto[1] = e;
            }
        }
    }
    // Print para controlar, se debe eliminar de esta funcion y mover a otra
    return;
}

void Estadisticas::MejorYPeorEquipo()
{
    cout << "Equipo con mas goles: " << Absoluto[1] << endl;
    cout << "Equipo con menos goles: " << Absoluto[2] << endl;
}

void Estadisticas::Ingresar(Partido &p, const int &pp)
{
    competiciones.insert(p.competicion);
    equipos.insert(p.equipolocal);
    equipos.insert(p.equipovisitante);
    ESTADISTICAS_EQUIPO temp, *ptemp;

    // Equipo Local
    ptemp = EstadisticasTodosLosEquipos.buscar(p.equipolocal + p.competicion);
    if (ptemp != nullptr)
    {
        temp = *ptemp;
        if (temp.fechas[0] < p.goleslocales)
        {
            temp.mejor_fecha = p.fecha;
            temp.fechas[0] = p.goleslocales;
        }
        if (temp.fechas[1] > p.goleslocales)
        {
            temp.peor_fecha = p.fecha;
            temp.fechas[1] = p.goleslocales;
        }
        temp.goles += p.goleslocales;
        temp.cgoles += p.golesvisitantes;
        if (p.goleslocales > p.golesvisitantes)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo luego
        *ptemp = temp;
    }
    else
    {
        ESTADISTICAS_EQUIPO temp;
        temp.mejor_fecha = p.fecha;
        temp.fechas[0] = p.goleslocales;
        temp.peor_fecha = p.fecha;
        temp.fechas[1] = p.goleslocales;
        temp.goles += p.goleslocales;
        temp.cgoles += p.golesvisitantes;
        if (p.goleslocales > p.golesvisitantes)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo luego
        EstadisticasTodosLosEquipos.put(p.equipolocal + p.competicion, temp);
    }
    ptemp = EstadisticasTodosLosEquipos.buscar(p.equipovisitante + p.competicion);
    if (ptemp != nullptr)
    {
        temp = *ptemp;
        if (temp.fechas[0] < p.golesvisitantes)
        {
            temp.mejor_fecha = p.fecha;
            temp.fechas[0] = p.golesvisitantes;
        }
        if (temp.fechas[1] > p.golesvisitantes)
        {
            temp.peor_fecha = p.fecha;
            temp.fechas[1] = p.golesvisitantes;
        }
        temp.goles += p.golesvisitantes;
        temp.cgoles += p.goleslocales;
        if (p.golesvisitantes > p.goleslocales)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo luego
        *ptemp = temp;
    }
    else
    {
        ESTADISTICAS_EQUIPO temp;
        temp.mejor_fecha = p.fecha;
        temp.fechas[0] = p.golesvisitantes;
        temp.peor_fecha = p.fecha;
        temp.fechas[1] = p.golesvisitantes;
        temp.goles += p.golesvisitantes;
        temp.cgoles += p.goleslocales;
        if (p.golesvisitantes > p.goleslocales)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo luego
        EstadisticasTodosLosEquipos.put(p.equipovisitante + p.competicion, temp);
    }

    MEJORES_PARTIDOS *px = Estadisticascompetencias.buscar(p.competicion), x;
    if (px != nullptr)
    {
        x = *px;
        x.goals += p.goleslocales + p.golesvisitantes;
        if ((p.goleslocales + p.golesvisitantes) >= (x.partidos[4].goleslocales + x.partidos[4].golesvisitantes))
        {
            x.mejor(p);
        }
        *px = x;
    }
    else
    {
        x.goals += p.goleslocales + p.golesvisitantes;
        x.partidos[0] = p;
        Estadisticascompetencias.put(p.competicion, x);
    }

    return;
}

vector<int> Estadisticas::getPartidosPor(string equipo, string competencia)
{
    try
    {
        return EstadisticasTodosLosEquipos.get(equipo + competencia).lista;
    }
    catch (const int &equipos)
    {
        vector<int> vacio;
        return vacio;
    }
}

void Estadisticas::printtodascompetencias()
{
    for (const auto &c : competiciones)
    {
        printcompetencia(c);
    }
}

void Estadisticas::MasGolesCompeticion()
{
    cout << "\nCompeticion con mas goles: " << Absoluto[0] << endl;
}

bool Estadisticas::EquipoyCompetenciaExiste(string hash)
{
    if (EstadisticasTodosLosEquipos.buscar(hash) != nullptr)
    {
        return true;
    }
    return false;
}

void Estadisticas::printcompetencia(string competencia)
{
    if (Estadisticascompetencias.buscar(competencia))
    {
        Estadisticascompetencias.get(competencia).print(competencia);
    }
    else
    {
        cout << "Error 404: Competencia inexistente" << endl;
    }
}
// Imprime tanto las estadisticas del equipo en esa competencia como las estadisticas de la competencia ingresada
void Estadisticas::print(string equipo, string competencia)
{
    if (EstadisticasTodosLosEquipos.buscar(equipo + competencia))
    {
        EstadisticasTodosLosEquipos.get(equipo + competencia).print();
    }
    else
    {
        cout << "\nError: 404\n";
        cout << "Equipo no encontrado en competicion ingresada";
    }
}

void Estadisticas::Goles(string equipo, string competencia)
{
    ESTADISTICAS_EQUIPO *px = EstadisticasTodosLosEquipos.buscar(equipo + competencia);
    if (px != nullptr)
    {
        cout << equipo << " a favor: " << px->goles << " ,en contra: " << px->cgoles << " ,en la competencia: " << competencia << endl;
    }
}
// Funcion para debug, solamente imprime cuantas casillas estan ocupadas en la tabla
void Estadisticas::llenado()
{ // Para saber si la tabla Hash es del tamaño correcto (143 de 10k xD), tenia razon...
    cout << "Llenado de tabla golespc: " << Estadisticascompetencias.espacioRestante() << endl;
    cout << "Llenado de tabla EstadisticasTodosLosEquipos: " << EstadisticasTodosLosEquipos.espacioRestante() << endl;
}

#endif