#include"libreria.h"
#include <sstream> //para stream

int main(){
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    getline(archivo,linea);
    
    while (getline(archivo, linea)) {
        stringstream stream(linea);
        // Jornada,Fecha,Equipo Local,Goles Local,Goles Visitante,Equipo Visitante,Competicion
        partido carga;
        getline(stream,carga.Jornada,',');
        getline(stream,carga.Fecha,',');
        getline(stream,carga.EquipoLocal,',');
        getline(stream,carga.GolesLocal,',');
        getline(stream,carga.GolesVisitante,',');
        getline(stream,carga.EquipoVisitante,',');
        getline(stream,carga.Competicion,',');
        //Aca pasa la magia pero no vale mirar atras de la cortina :(
        cupholder.add(carga);
    }

    archivo.close();
}