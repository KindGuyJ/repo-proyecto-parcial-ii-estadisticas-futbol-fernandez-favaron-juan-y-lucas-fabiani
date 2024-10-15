#include <ctime>
#include "libreria.h"
#include <iomanip>
#include <unordered_set>
#include "MiHash.h"

using namespace std;

unsigned int customHashFunc(std::string clave) {
    unsigned int hash = 0;
    for (char c : clave) {
        hash = hash * 37 + static_cast<unsigned int>(c);
    }
    return hash;
}

struct statsequipo{
    int win =0;
    int lost =0;
    int goles=0;
    int cgoles=0; //te metieron
    int Fechas[2] = {0,0}; //[0] es Mejor y [1] es Peor
    int partidos=0;
    Date MejorFecha;
    Date PeorFecha;
    vector<int> lista;

    void print(){
        cout << "Victorias: " << win << endl;
        cout << "Derrotas: " << lost << endl;
        cout << "Goles a favor: " << goles << endl;
        cout << "Goles del oponente: " << cgoles << endl;
        cout << "Goles a favor en promedio: " << static_cast<float>(goles)/partidos << endl;
        cout << "Goles del oponente en promedio: " << static_cast<float>(cgoles)/partidos << endl;
        cout << "Mejor fecha: " << MejorFecha.toString() << endl;
        cout << "Peor fecha: " << PeorFecha.toString() << endl;
        cout << "Partidos: " << partidos << endl;
        /*partidos todos
        cout<<"Partidos jugados: "<<endl;
        cout<<setw(25)<<"Jornada"<<setw(8)<<"\tFecha"<<setw(30)<<"\tEquipo Local"<<setw(30)<<"\tEquipo Visitante"<<setw(8)<<"\tGoles Local"<<setw(10)<<"\tGoles Visitante\n";
        for (int i=0;i<lista.size();i++)
        {
            cout << setw(25) << lista[i]->Jornada << "\t"
                 << setw(8) << lista[i]->Fecha.toString() << "\t"
                 << setw(30) << lista[i]->EquipoLocal << "\t"
                 << setw(30) << lista[i]->EquipoVisitante << "\t"
                 << setw(8) << lista[i]->GolesLocal << "\t"
                 << setw(10) << lista[i]->GolesVisitante << "\n";
        }*/

    }

};

class Stats
{
private:
    unordered_set<string> competiciones;
    HashMap<std::string,int> golesporcompetencia;
    HashMap<std::string,statsequipo> BigData;
public:
    Stats();
    ~Stats();
    void Ingresar(partido &p); //Se puede usar para cargar el partido desde cupholder
    void print(string equipo, string competencia); //No es final, solo debugging
    void llenado(); 

};

Stats::Stats():golesporcompetencia(30, customHashFunc), BigData(1000, customHashFunc) {
}
Stats::~Stats()
{
};

void Stats::Ingresar(partido &p)
{
    competiciones.insert(p.Competicion);
    statsequipo temp;
    //Equipo Local
    try {
        temp = BigData.get(p.EquipoLocal+p.Competicion);
        if (temp.Fechas[0]<p.GolesLocal) temp.MejorFecha=p.Fecha; temp.Fechas[0]=p.GolesLocal;
        if (temp.Fechas[1]>p.GolesLocal) temp.PeorFecha=p.Fecha; temp.Fechas[1]=p.GolesLocal;
        temp.goles += p.GolesLocal;
        temp.cgoles += p.GolesVisitante;
        if (p.GolesLocal>p.GolesVisitante) temp.win++;
        else temp.lost++;
        temp.partidos++;
        temp.lista.push_back(&p);//Para llamar los partidos del equipo
        BigData.put(p.EquipoLocal+p.Competicion,temp);
    }
    catch(int e){
        statsequipo temp;
        if (temp.Fechas[0]<p.GolesLocal) temp.MejorFecha=p.Fecha; temp.Fechas[0]=p.GolesLocal;
        temp.PeorFecha=p.Fecha; temp.Fechas[1]=p.GolesLocal;
        temp.goles += p.GolesLocal;
        temp.cgoles += p.GolesVisitante;
        if (p.GolesLocal>p.GolesVisitante) temp.win++;
        else temp.lost++;
        temp.partidos++;
        temp.lista.push_back(&p);//Para llamar los partidos del equipo
        BigData.put(p.EquipoLocal+p.Competicion,temp);
    }

    //Equipo Visitante
    try {
        temp = BigData.get(p.EquipoVisitante+p.Competicion);
        if (temp.Fechas[0]<p.GolesVisitante) temp.MejorFecha=p.Fecha; temp.Fechas[0]=p.GolesVisitante;
        if (temp.Fechas[1]>p.GolesVisitante) temp.PeorFecha=p.Fecha; temp.Fechas[1]=p.GolesVisitante;
        temp.goles += p.GolesVisitante;
        temp.cgoles += p.GolesLocal;
        if (p.GolesVisitante>p.GolesLocal) temp.win++;
        else temp.lost++;
        temp.partidos++;
        temp.lista.push_back(&p);//Para llamar los partidos del equipo
        BigData.put(p.EquipoVisitante+p.Competicion,temp);
    }
    catch(int e){
        statsequipo temp;
        if (temp.Fechas[0]<p.GolesVisitante) temp.MejorFecha=p.Fecha; temp.Fechas[0]=p.GolesVisitante;
        temp.PeorFecha=p.Fecha; temp.Fechas[1]=p.GolesVisitante;
        temp.goles += p.GolesVisitante;
        temp.cgoles += p.GolesLocal;
        if (p.GolesVisitante>p.GolesLocal) temp.win++;
        else temp.lost++;
        temp.partidos++;
        temp.lista.push_back(&p);//Para llamar los partidos del equipo
        BigData.put(p.EquipoVisitante+p.Competicion,temp);
    }

    //Goles por competencia
    try
    {
        int x=golesporcompetencia.get(p.Competicion);
        x += p.GolesLocal+p.GolesVisitante;
        golesporcompetencia.put(p.Competicion,x);
    }
    catch(int e)
    {
        golesporcompetencia.put(p.Competicion,p.GolesLocal+p.GolesVisitante);
    }
    

}

void Stats::print(string equipo, string competencia){
    try
    {
        BigData.get(equipo+competencia).print();
    }
    catch(int e)
    {
        cout << "Error: "<<e << '\n';
    }
    
}

void Stats::llenado(){ //Para saber si la tabla Hash es del tamaño correcto (143 de 10k xD), probablemente si pero soy autista
    cout<<"Llenado de tabla golespc: "<<golesporcompetencia.espacioRestante()<<endl;
    cout<<"Llenado de tabla BigData: "<<BigData.espacioRestante()<<endl;

}

int main() {
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    Stats allstats;
    getline(archivo,linea); //Header

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    while (getline(archivo, linea)) {
        stringstream stream(linea);
        // Jornada,Fecha,Equipo Local,Goles Local,Goles Visitante,Equipo Visitante,Competicion
        partido carga;
        string temp;
        getline(stream,carga.Jornada,',');
        getline(stream,temp,',');
        carga.Fecha = temp;
        getline(stream,carga.EquipoLocal,',');
        getline(stream,temp,',');
        carga.GolesLocal = stoi(temp);
        getline(stream,temp,',');
        carga.GolesVisitante = stoi(temp);
        getline(stream,carga.EquipoVisitante,',');
        getline(stream,carga.Competicion,',');
        //Aca pasa la magia pero no vale mirar atras de la cortina :(
        cupholder.add(carga);
        allstats.Ingresar(carga,cupholder.last());
    }
    clock_t end = clock();

    archivo.close();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << endl;
    string a,b;
    cout<<"Ingresar equipo,competencia a consultar"<<endl;
    getline(cin,a);
    getline(cin,b);
    allstats.print(a,b);
    //Tardo elapsed_secs: 0.017
    allstats.llenado();
    return 0;
}
