#include <ctime> //Para clock_t
#include"libreria.h"
#include <sstream> //para stream

int main(){
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    getline(archivo,linea);
    
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        // Jornada,Fecha,Equipo Local,Goles Local,Goles Visitante,Equipo Visitante,Competicion
        partido carga;
        string temp;
        getline(stream,carga.Jornada,',');
        getline(stream,carga.Fecha,',');
        getline(stream,carga.EquipoLocal,',');
        getline(stream,temp,',');
        carga.GolesLocal = stoi(temp);
        getline(stream,temp,',');
        carga.GolesVisitante = stoi(temp);
        getline(stream,carga.EquipoVisitante,',');
        getline(stream,carga.Competicion,',');
        //Aca pasa la magia pero no vale mirar atras de la cortina :(
        cupholder.add(carga);
    }

    clock_t end = clock();
    archivo.close();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;
}