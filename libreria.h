#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> //para stream
#include <iomanip> //para setw
#include <unordered_set>
#include "MiHash.h"

using namespace std;

struct Date
{
    int dia, mes, year;

    Date(const string &s)
    {
        sscanf(s.c_str(), "%d/%d/%d", &dia, &mes, &year);
    }

    Date()
    {
        dia = 0;
        mes = 0;
        year = 0;
    }

    bool operator>(const Date &other) const
    {
        if (year != other.year)
            return year > other.year;
        if (mes != other.mes)
            return mes > other.mes;
        return dia > other.dia;
    }

    bool operator<(const Date &other) const
    { // totalmente innecesario
        if (year != other.year)
            return year < other.year;
        if (mes != other.mes)
            return mes < other.mes;
        return dia < other.dia;
    }

    bool operator==(const Date &other) const
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

struct partido
{
    string Jornada = "";
    Date Fecha;
    string EquipoLocal = "";
    int GolesLocal = 0;
    int GolesVisitante = 0;
    string EquipoVisitante = "";
    string Competicion = "";
};

struct BestofCompetencia
{
    int goals;
    partido partidos[5];
    string bestteam;
    string worstteam;

    // Movido como funcion del struct pero puede ser una funcion aparte idealmente.
    void print(string competencia)
    {
        cout << endl
             << "Competicion: " << competencia << endl;
        cout << setw(25) << "Jornada" << setw(8) << "\tFecha" << setw(30) << "\tEquipo Local" << setw(30) << "\tEquipo Visitante" << setw(8) << "\tGoles Local" << setw(10) << "\tGoles Visitante\n";
        for (int i = 5; i > 0; i--)
        {
            cout << setw(25) << partidos[i - 1].Jornada << "\t"
                 << setw(8) << partidos[i - 1].Fecha.toString() << "\t"
                 << setw(30) << partidos[i - 1].EquipoLocal << "\t"
                 << setw(30) << partidos[i - 1].EquipoVisitante << "\t"
                 << setw(8) << partidos[i - 1].GolesLocal << "\t"
                 << setw(10) << partidos[i - 1].GolesVisitante << "\n";
        }
    }

    void best(partido x)
    {
        for (int i = 0; i < 5; i++)
        {
            if ((x.GolesLocal + x.GolesVisitante) > (partidos[i].GolesLocal + partidos[i].GolesVisitante))
            {
                partido t = partidos[i];
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
        if ((x.GolesLocal + x.GolesVisitante) == (partidos[0].GolesLocal + partidos[0].GolesVisitante))
        {
            // Ordeno los 5 que ya estaban por fecha
            for (int i = 0; i < 5; i++)
            {
                for (int j = 1; j < 5; j++)
                {
                    if ((partidos[i].Fecha) < (partidos[j].Fecha))
                    {
                        partido t = partidos[i];
                        partidos[i] = partidos[j];
                        partidos[j] = t;
                    }
                }
            }
            for (int i = 0; i < 5; i++)
            {
                if ((x.Fecha) > (partidos[i].Fecha))
                {
                    partido t = partidos[i];
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

struct statsequipo
{
    int win = 0;
    int lost = 0;
    int goles = 0;
    int cgoles = 0;         // te metieron
    int Fechas[2] = {0, 0}; //[0] es Mejor y [1] es Peor
    int partidos = 0;
    Date MejorFecha;
    Date PeorFecha;
    vector<int> lista;

    void print()
    {
        cout << "Victorias: " << win << endl;
        cout << "Derrotas: " << lost << endl;
        cout << "Goles a favor: " << goles << endl;
        cout << "Goles del oponente: " << cgoles << endl;
        cout << "Goles a favor en promedio: " << static_cast<float>(goles) / partidos << endl;
        cout << "Goles del oponente en promedio: " << static_cast<float>(cgoles) / partidos << endl;
        cout << "Mejor fecha: " << MejorFecha.toString() << endl;
        cout << "Peor fecha: " << PeorFecha.toString() << endl;
        cout << "Partidos: " << partidos << endl;
    }
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
    // fuckit
    int last()
    {
        return data.size() - 1;
    }

    // no tendriamos que usar esta funcion directamente porque es un print en el objeto y tendriamos que hacer el print en main
    void printlista(vector<int> lista)
    {
        // partidos todos
        cout << "Partidos jugados: " << endl;
        cout << setw(25) << "Jornada" << setw(8) << "\tFecha" << setw(30) << "\tEquipo Local" << setw(30) << "\tEquipo Visitante" << setw(8) << "\tGoles Local" << setw(10) << "\tGoles Visitante\n";
        for (int i = 0; i < lista.size(); i++)
        {
            cout << setw(25) << data[lista[i]].Jornada << "\t"
                 << setw(8) << data[lista[i]].Fecha.toString() << "\t"
                 << setw(30) << data[lista[i]].EquipoLocal << "\t"
                 << setw(30) << data[lista[i]].EquipoVisitante << "\t"
                 << setw(8) << data[lista[i]].GolesLocal << "\t"
                 << setw(10) << data[lista[i]].GolesVisitante << "\n";
        }
    }
    // para hacer print en main...
    vector<partido> bringlista(vector<int> lista)
    {
        // filtrar en main o otra funcion mas
        vector<partido> truelista;
        for (int i = 0; i < lista.size(); i++)
        {
            truelista.push_back(data[lista[i]]);
        }
        return truelista;
    }
};
// Funcion de hash basada en FNV-1
unsigned int customHashFunc(string clave)
{
    const unsigned int FNV_PRIME = 16777619u;
    const unsigned int OFFSET_BASIS = 2166136261u;

    unsigned int hash = OFFSET_BASIS;
    for (char c : clave)
    {
        hash = hash * FNV_PRIME;
        hash = hash ^ static_cast<unsigned int>(c);
    }
    return hash;
}

class Stats
{
private:
    unordered_set<string> competiciones;
    unordered_set<string> equipos;
    HashMap<std::string, BestofCompetencia> statscompetencias;
    HashMap<std::string, statsequipo> BigData;
    //[0] mejor competicion por cantidad de goles, [1] equipo con mas goles, [2] equipo con menos goles
    string Absoluto[3];

public:
    Stats();
    ~Stats();
    void Ingresar(partido &p, int pp);             // Se puede usar para cargar el partido desde cupholder
    void print(string equipo, string competencia); // No es final, solo debugging
    void llenado();
    void Calculofinal();
    vector<int> partidos(string equipo, string competencia);
};

Stats::Stats() : statscompetencias(30, customHashFunc), BigData(1000, customHashFunc)
{
}
Stats::~Stats() {
};

void Stats::Calculofinal()
{
    cout << competiciones.size() << endl;
    cout << equipos.size() << endl;

    // Logica para peor y mejor equipo por cantidad de goles, mejorable...
    string best, worst;
    int cbest = 0, cbestest = 0, cworstest = 1000, cworst = 1000, cgoles = 0;
    // Este for hace aprox 600 ejecuciones porque intenta buscar muchos stats
    // De equipos que no jugaron en ciertas competencias. en 4k partidos hay
    //~130 equipos y 5 competiciones pero solo ~148stats de equipos (la mayoria de equipos solo juega en una competicion)
    for (const auto &c : competiciones)
    {
        cbest = 0, cworst = 1000;
        for (const auto &e : equipos)
        {
            try
            {
                statsequipo x = BigData.get(e + c);
                if (cworst > x.cgoles + x.goles)
                {
                    cworst = x.cgoles + x.goles;
                    worst = e;
                }
                if (cbest < x.cgoles + x.goles)
                {
                    cbest = x.cgoles + x.goles;
                    best = e;
                }
            }
            catch (int)
            {
                // van a saltar muchos int porque cuando el hash no encuentre un partido tira int.
                // No se una formar mas facil de recorrer el hash sin modificar muchisimo la libreria...
            }
        }
        BestofCompetencia y = statscompetencias.get(c);
        y.bestteam = best;
        y.worstteam = worst;
        statscompetencias.put(c, y);
        // Solo un sith se maneja en absolutos
        if (cworstest > cworst)
        {
            Absoluto[2] = worst;
            cworstest = cworst;
        }
        if (cbest > cbestest)
        {
            Absoluto[1] = best;
            cbestest = cbest;
        }
        if (cgoles < y.goals)
        {
            Absoluto[0] = c;
            cgoles = y.goals;
        }
    }
    cout << "Competicion con mas goles: " << Absoluto[0] << endl;
    cout << "Equipo con mas goles: " << Absoluto[1] << " ,con: " << cbestest << endl;
    cout << "Equipo con menos goles: " << Absoluto[2] << " ,con: " << cworstest << endl;
    cout << endl
         << "Equipos con mas y menos goles por competicion:" << endl;
    for (const auto &c : competiciones)
    {
        cout << "Competicion: " << c << endl;
        cout << "   Mas goles: " << statscompetencias.get(c).bestteam << endl;
        cout << "   Menos goles: " << statscompetencias.get(c).worstteam << endl
             << endl;
    }
}

void Stats::Ingresar(partido &p, int pp)
{
    competiciones.insert(p.Competicion);
    equipos.insert(p.EquipoLocal);
    equipos.insert(p.EquipoVisitante);
    statsequipo temp;
    // Equipo Local
    try
    {
        temp = BigData.get(p.EquipoLocal + p.Competicion);
        if (temp.Fechas[0] < p.GolesLocal)
            temp.MejorFecha = p.Fecha;
        temp.Fechas[0] = p.GolesLocal;
        if (temp.Fechas[1] > p.GolesLocal)
            temp.PeorFecha = p.Fecha;
        temp.Fechas[1] = p.GolesLocal;
        temp.goles += p.GolesLocal;
        temp.cgoles += p.GolesVisitante;
        if (p.GolesLocal > p.GolesVisitante)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo
        BigData.put(p.EquipoLocal + p.Competicion, temp);
    }
    catch (int e)
    {
        statsequipo temp;
        temp.MejorFecha = p.Fecha;
        temp.Fechas[0] = p.GolesLocal;
        temp.PeorFecha = p.Fecha;
        temp.Fechas[1] = p.GolesLocal;
        temp.goles += p.GolesLocal;
        temp.cgoles += p.GolesVisitante;
        if (p.GolesLocal > p.GolesVisitante)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo
        BigData.put(p.EquipoLocal + p.Competicion, temp);
    }

    // Equipo Visitante
    try
    {
        temp = BigData.get(p.EquipoVisitante + p.Competicion);
        if (temp.Fechas[0] < p.GolesVisitante)
            temp.MejorFecha = p.Fecha;
        temp.Fechas[0] = p.GolesVisitante;
        if (temp.Fechas[1] > p.GolesVisitante)
            temp.PeorFecha = p.Fecha;
        temp.Fechas[1] = p.GolesVisitante;
        temp.goles += p.GolesVisitante;
        temp.cgoles += p.GolesLocal;
        if (p.GolesVisitante > p.GolesLocal)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo
        BigData.put(p.EquipoVisitante + p.Competicion, temp);
    }
    catch (int e)
    {
        statsequipo temp;
        temp.MejorFecha = p.Fecha;
        temp.Fechas[0] = p.GolesVisitante;
        temp.PeorFecha = p.Fecha;
        temp.Fechas[1] = p.GolesVisitante;
        temp.goles += p.GolesVisitante;
        temp.cgoles += p.GolesLocal;
        if (p.GolesVisitante > p.GolesLocal)
            temp.win++;
        else
            temp.lost++;
        temp.partidos++;
        temp.lista.push_back(pp); // Para llamar los partidos del equipo
        BigData.put(p.EquipoVisitante + p.Competicion, temp);
    }

    // Goles por competencia
    try
    {
        BestofCompetencia x = statscompetencias.get(p.Competicion);
        x.goals += p.GolesLocal + p.GolesVisitante;
        statscompetencias.put(p.Competicion, x);
        if ((p.GolesLocal + p.GolesVisitante) >= (x.partidos[4].GolesLocal + x.partidos[4].GolesVisitante))
        {
            x.best(p);
        }
        statscompetencias.put(p.Competicion, x);
    }
    catch (int e)
    {
        BestofCompetencia x;
        x.goals += p.GolesLocal + p.GolesVisitante;
        x.partidos[0] = p;
        statscompetencias.put(p.Competicion, x);
    }
}

vector<int> Stats::partidos(string equipo, string competencia)
{
    return BigData.get(equipo + competencia).lista;
}

void Stats::print(string equipo, string competencia)
{
    try
    {
        BigData.get(equipo + competencia).print();
    }
    catch (int e)
    {
        cout << "Error: " << e << '\n';
        if (e == 404)
        {
            cout << "Equipo no encontrado en competicion ingresada";
        }
    }
    try
    {
        statscompetencias.get(competencia).print(competencia);
    }
    catch (int e)
    {
        cout << "Error: " << e << '\n';
        if (e == 404)
        {
            cout << "Competencia inexistente";
        }
    }
}

void Stats::llenado()
{ // Para saber si la tabla Hash es del tamaño correcto (143 de 10k xD), tenia razon...
    cout << "Llenado de tabla golespc: " << statscompetencias.espacioRestante() << endl;
    cout << "Llenado de tabla BigData: " << BigData.espacioRestante() << endl;
}
