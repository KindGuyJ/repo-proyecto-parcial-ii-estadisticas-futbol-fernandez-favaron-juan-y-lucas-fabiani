#include <ctime>
#include "libreria.h"

using namespace std;

int main() {
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    Stats allstats;
    getline(archivo,linea); //Header

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();

    int c=0;
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
        allstats.Ingresar(carga,c);
        c++; //se puede usar cupholder.last() pero esto deberia ser mas rapido que llamar a una funcion...
    }
    allstats.Calculofinal();
    clock_t end = clock();

    archivo.close();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << endl;
    string a,b;
    cout<<"Ingresar equipo,competencia a consultar"<<endl;
    a = "Milan";
    b = "Champions League";
    allstats.print(a,b);
    cupholder.printlista(allstats.partidos(a,b));
    //Tardo elapsed_secs: 0.017
    //Tardo elapsed_secs: 0.067
    allstats.llenado();
    return 0;
}
