#include <iostream>
#include <vector> //Lista optimizada
#include <fstream>
#include <sstream> //para stream
#include <iomanip> //para setw
#include <unordered_set>
#include "MiHash.h" //OpenHashing

using namespace std;

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
struct PARTIDO
{
    string jornada = "";
    FECHA fecha;
    string equipolocal = "";
    int goleslocales = 0;
    int golesvisitantes = 0;
    string equipovisitante = "";
    string competicion = "";
};

struct MEJORES_PARTIDOS
{
    int goals = 0;
    PARTIDO PARTIDOs[5];
    string mejorequipo;
    string peorequipo;

    // Movido como funcion del struct pero puede ser una funcion aparte idealmente.
    void print(string competencia)
    {
        cout << endl
             << "Competicion: " << competencia << endl;
        cout << setw(25) << "Jornada" << setw(8) << "\tFecha" << setw(30) << "\tEquipo Local" << setw(30) << "\tEquipo Visitante" << setw(8) << "\tGoles Local" << setw(10) << "\tGoles Visitante\n";
        for (int i = 5; i > 0; i--)
        {
            cout << setw(25) << PARTIDOs[i - 1].jornada << "\t"
                 << setw(8) << PARTIDOs[i - 1].fecha.toString() << "\t"
                 << setw(30) << PARTIDOs[i - 1].equipolocal << "\t"
                 << setw(30) << PARTIDOs[i - 1].equipovisitante << "\t"
                 << setw(8) << PARTIDOs[i - 1].goleslocales << "\t"
                 << setw(10) << PARTIDOs[i - 1].golesvisitantes << "\n";
        }
    }

    void mejor(PARTIDO x)
    {
        for (int i = 0; i < 5; i++)
        {
            if ((x.goleslocales + x.golesvisitantes) > (PARTIDOs[i].goleslocales + PARTIDOs[i].golesvisitantes))
            {
                PARTIDO t = PARTIDOs[i];
                PARTIDOs[i] = x;
                for (int j = i + 1; j < 5; j++)
                {
                    x = PARTIDOs[j];
                    PARTIDOs[j] = t;
                    t = x;
                }
                return;
            }
        }
        // si los 5 PARTIDOs tienen los mismos goles se ejecuta esto, que no es lindo pero simple
        if ((x.goleslocales + x.golesvisitantes) == (PARTIDOs[0].goleslocales + PARTIDOs[0].golesvisitantes))
        {
            // Ordeno los 5 que ya estaban por FECHA
            for (int i = 0; i < 5; i++)
            {
                for (int j = 1; j < 5; j++)
                {
                    if ((PARTIDOs[i].fecha) < (PARTIDOs[j].fecha))
                    {
                        PARTIDO t = PARTIDOs[i];
                        PARTIDOs[i] = PARTIDOs[j];
                        PARTIDOs[j] = t;
                    }
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if ((x.fecha) > (PARTIDOs[i].fecha))
                {
                    PARTIDO t = PARTIDOs[i];
                    PARTIDOs[i] = x;
                    for (int j = i + 1; j < 5; j++)
                    {
                        x = PARTIDOs[j];
                        PARTIDOs[j] = t;
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
        cout << "Goles a favor en promedio: " << static_cast<float>(goles) / partidos << endl;
        cout << "Goles del oponente en promedio: " << static_cast<float>(cgoles) / partidos << endl;
        cout << "Mejor fecha: " << mejor_fecha.toString() << endl;
        cout << "Peor fecha: " << peor_fecha.toString() << endl;
        cout << "Partidos: " << partidos << endl;
    }
};
// Clase para almacenar una lista de partidos y funciones para modificar los mismos.
// Capaz cambiar el asignar y get para que den el objeto pero bueno no los use para nada todavia.
class ALMACEN
{
private:
    vector<PARTIDO> informacion;

public:
    void agregar(PARTIDO s)
    {
        informacion.push_back(s);
    }
    /// @brief
    /// @param o A cual de todos los vectores asignar
    /// @param x Nuevo string
    /// @param i [0-6] 0-jornada; 1-fecha; 2-equipolocal; 3-goleslocales; 4-golesvisitantes; 5-equipovisitante; 6-competicion;
    void assign(int o, string x, int i)
    {
        switch (i)
        {
        case 0:
            informacion[o].jornada = x;
            break;
        case 1:
            informacion[o].fecha = x;
            break;
        case 2:
            informacion[o].equipolocal = x;
            break;
        case 3:
            informacion[o].goleslocales = stoi(x);
            break;
        case 4:
            informacion[o].golesvisitantes = stoi(x);
            break;
        case 5:
            informacion[o].equipovisitante = x;
            break;
        case 6:
            informacion[o].competicion = x;
            break;
        default:
            throw 666 - 1;
            break;
        }
    }
    /// @brief
    /// @param o A cual vector leer
    /// @param i [0-6] 0-jornada; 1-fecha; 2-equipolocal; 3-goleslocales; 4-golesvisitantes; 5-equipovisitante; 6-competicion;
    /// @return la informacion
    string get(int o, int i)
    {
        switch (i)
        {
        case 0:
            return informacion[o].jornada;
            break;
        case 1:
            return informacion[o].fecha.toString();
            break;
        case 2:
            return informacion[o].equipolocal;
            break;
        case 3:
            return to_string(informacion[o].goleslocales);
            break;
        case 4:
            return to_string(informacion[o].golesvisitantes);
            break;
        case 5:
            return informacion[o].equipovisitante;
            break;
        case 6:
            return informacion[o].competicion;
            break;
        default:
            throw 666 - 2;
            break;
        }
    }
    // Reenvia la ubicacion del ultimo partido agregado
    int last()
    {
        return informacion.size() - 1;
    }

    // Imprime vectores guardados en el objecto si sus posiciones coinciden con los valores de la lista
    void printlista(vector<int> lista)
    {
        // If se ejecuta si no encuentra ningun partido
        if (lista.size() == 0)
        {
            return;
        }

        cout << "Partidos jugados: " << endl;
        cout << setw(25) << "Jornada" << setw(8) << "\tFecha" << setw(30) << "\tEquipo Local" << setw(30) << "\tEquipo Visitante" << setw(8) << "\tGoles Local" << setw(10) << "\tGoles Visitante\n";
        for (int i = 0; i < lista.size(); i++)
        {
            cout << setw(25) << informacion[lista[i]].jornada << "\t"
                 << setw(8) << informacion[lista[i]].fecha.toString() << "\t"
                 << setw(30) << informacion[lista[i]].equipolocal << "\t"
                 << setw(30) << informacion[lista[i]].equipovisitante << "\t"
                 << setw(8) << informacion[lista[i]].goleslocales << "\t"
                 << setw(10) << informacion[lista[i]].golesvisitantes << "\n";
        }
    }
    // para hacer print en main...
    vector<PARTIDO> TraerPartidos(vector<int> lista)
    {
        // filtrar en main o otra funcion mas
        vector<PARTIDO> partidos;
        for (int i = 0; i < lista.size(); i++)
        {
            partidos.push_back(informacion[lista[i]]);
        }
        return partidos;
    }
};
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
    void Ingresar(PARTIDO &p, const int &pp);      // Se puede usar para cargar el PARTIDO desde cupholder
    void print(string equipo, string competencia); // No es final, solo debugging
    void llenado();
    void Calculofinal();
    vector<int> PARTIDOs(string equipo, string competencia);
};

Estadisticas::Estadisticas() : Estadisticascompetencias(30, customHashFunc), EstadisticasTodosLosEquipos(1000, customHashFunc)
{
}
Estadisticas::~Estadisticas() {
};

void Estadisticas::Calculofinal()
{
    cout << competiciones.size() << endl;
    cout << equipos.size() << endl;

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
        int co=0;cmejor = 0; cpeor = 1000;
        for (const auto &e : equipos)
        {
            co=0;
            for (const auto &c : competiciones)
            {
                ESTADISTICAS_EQUIPO *px = EstadisticasTodosLosEquipos.buscar(e+c);
                if (px!=nullptr){
                    co += px->goles;
                }
            }
            if (co<cpeor){
                cpeor = co;
                Absoluto[2] = e;
            }
            if (co>cmejor){
                cmejor = co;
                Absoluto[1] = e;
            }
        }
    }
    // Print para controlar, se debe eliminar de esta funcion y mover a otra
    cout << "Competicion con mas goles: " << Absoluto[0] << endl;
    cout << "Equipo con mas goles: " << Absoluto[1] << " ,con: " << cmejor << endl;
    cout << "Equipo con menos goles: " << Absoluto[2] << " ,con: " << cpeor << endl;
    cout << endl
         << "Equipos con mas y menos goles por competicion:" << endl;
    for (const auto &competencia : competiciones)
    {
        cout << "Competicion: " << competencia << endl;
        cout << "   Mas goles: " << Estadisticascompetencias.get(competencia).mejorequipo << endl;
        cout << "   Menos goles: " << Estadisticascompetencias.get(competencia).peorequipo << endl
             << endl;
    }
    return;
}

void Estadisticas::Ingresar(PARTIDO &p, const int &pp)
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
        if ((p.goleslocales + p.golesvisitantes) >= (x.PARTIDOs[4].goleslocales + x.PARTIDOs[4].golesvisitantes))
        {
            x.mejor(p);
        }
        *px = x;
    }
    else
    {
        x.goals += p.goleslocales + p.golesvisitantes;
        x.PARTIDOs[0] = p;
        Estadisticascompetencias.put(p.competicion, x);
    }

    return;
}

vector<int> Estadisticas::PARTIDOs(string equipo, string competencia)
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

// Imprime tanto las estadisticas del equipo en esa competencia como las estadisticas de la competencia ingresada
void Estadisticas::print(string equipo, string competencia)
{
    try
    {
        EstadisticasTodosLosEquipos.get(equipo + competencia).print();
    }
    catch (int equipos)
    {
        cout << "\nError: " << equipos << '\n';
        if (equipos == 404)
        {
            cout << "Equipo no encontrado en competicion ingresada";
        }
    }
    try
    {
        Estadisticascompetencias.get(competencia).print(competencia);
    }
    catch (int equipos)
    {
        cout << "\nError: " << equipos << '\n';
        if (equipos == 404)
        {
            cout << "Competencia inexistente";
        }
    }
}

// Funcion para debug, solamente imprime cuantas casillas estan ocupadas en la tabla
void Estadisticas::llenado()
{ // Para saber si la tabla Hash es del tamaño correcto (143 de 10k xD), tenia razon...
    cout << "Llenado de tabla golespc: " << Estadisticascompetencias.espacioRestante() << endl;
    cout << "Llenado de tabla EstadisticasTodosLosEquipos: " << EstadisticasTodosLosEquipos.espacioRestante() << endl;
}
