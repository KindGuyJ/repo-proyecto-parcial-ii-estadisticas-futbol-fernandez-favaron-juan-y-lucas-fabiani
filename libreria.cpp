#include "libreria.h"

// FECHA struct methods
FECHA::FECHA(const string &s) {
    sscanf(s.c_str(), "%d/%d/%d", &dia, &mes, &year);
}

FECHA::FECHA() : dia(0), mes(0), year(0) {}

bool FECHA::operator>(const FECHA &other) const {
    if (year != other.year) return year > other.year;
    if (mes != other.mes) return mes > other.mes;
    return dia > other.dia;
}

bool FECHA::operator<(const FECHA &other) const {
    if (year != other.year) return year < other.year;
    if (mes != other.mes) return mes < other.mes;
    return dia < other.dia;
}

bool FECHA::operator==(const FECHA &other) const {
    return (year == other.year && mes == other.mes && dia == other.dia);
}

std::string FECHA::toString() const {
    std::ostringstream oss;
    oss << dia << "/" << mes << "/" << year;
    return oss.str();
}

// MEJORES_PARTIDOS struct methods
void MEJORES_PARTIDOS::print(string competencia) {
    cout << "\nCompeticion: " << competencia << endl
         << "Goles convertidos en la competencia: " << goals << endl
         << "Mejor equipo por goles convertidos: " << mejorequipo << endl
         << "Peor equipo por goles convertidos: " << peorequipo << endl;
    // Continue with your detailed print code
}

void MEJORES_PARTIDOS::mejor(PARTIDO x) {
    // Your sorting logic here
}

// ESTADISTICAS_EQUIPO struct methods
void ESTADISTICAS_EQUIPO::print() {
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

// ALMACEN class methods
void ALMACEN::agregar(PARTIDO s) { informacion.push_back(s); }

void ALMACEN::assign(int o, string x, int i) {
    switch (i) {
        // Code for assigning values
    }
}

string ALMACEN::get(int o, int i) {
    // Code for retrieving values
}

int ALMACEN::last() { return informacion.size() - 1; }

void ALMACEN::printlista(vector<int> lista) {
    if (lista.empty()) return;
    cout << "Partidos jugados: " << endl;
    // Detailed print code here
}

vector<PARTIDO> ALMACEN::TraerPartidos(vector<int> lista) {
    vector<PARTIDO> partidos;
    for (int i : lista) partidos.push_back(informacion[i]);
    return partidos;
}

// customHashFunc implementation
unsigned int customHashFunc(string clave) {
    const unsigned int FNV_PRIME = 16777619u;
    const unsigned int OFFSET_BASIS = 2166136261u;
    unsigned int hash = OFFSET_BASIS;
    for (char c : clave) {
        hash *= FNV_PRIME;
        hash ^= static_cast<unsigned int>(c);
    }
    return hash;
}

// Estadisticas class methods
Estadisticas::Estadisticas() : Estadisticascompetencias(30, customHashFunc), EstadisticasTodosLosEquipos(1000, customHashFunc) {}

Estadisticas::~Estadisticas() {}

void Estadisticas::Calculofinal() {
    // Implement calculations
}

void Estadisticas::MejorYPeorEquipo() {
    cout << "Equipo con mas goles: " << Absoluto[1] << " ,con: " << endl;
    cout << "Equipo con menos goles: " << Absoluto[2] << " ,con: " << endl;
}

void Estadisticas::Ingresar(PARTIDO &p, const int &pp) {
    // Code for inserting data
}

vector<int> Estadisticas::PARTIDOs(string equipo, string competencia) {
    try {
        return EstadisticasTodosLosEquipos.get(equipo + competencia).lista;
    } catch (...) {
        return {};
    }
}

void Estadisticas::printtodascompetencias() {
    for (const auto &c : competiciones) {
        printcompetencia(c);
    }
}

void Estadisticas::MasGolesCompeticion() {
    cout << "\nCompeticion con mas goles: " << Absoluto[0] << endl;
}

void Estadisticas::printcompetencia(string competencia) {
    if (Estadisticascompetencias.buscar(competencia))
        Estadisticascompetencias.get(competencia).print(competencia);
    else
        cout << "\nError: 404\nCompetencia inexistente\n";
}

void Estadisticas::print(string equipo, string competencia) {
    if (EstadisticasTodosLosEquipos.buscar(equipo + competencia))
        EstadisticasTodosLosEquipos.get(equipo + competencia).print();
    else
        cout << "\nError: 404\nEquipo no encontrado en competicion ingresada\n";
}

void Estadisticas::llenado() {
    cout << "Llenado de tabla golespc: " << Estadisticascompetencias.espacioRestante() << endl;
    cout << "Llenado de tabla EstadisticasTodosLosEquipos: " << EstadisticasTodosLosEquipos.espacioRestante() << endl;
}
