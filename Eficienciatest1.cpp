#include <ctime>
#include"libreria.h"
#include <sstream> //para stream

using namespace std;

int main() {
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    top5 best;
    getline(archivo,linea);

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
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
        for (int i = 0; i < 20; i++)
        {
            if (best.competiciones[i]==carga.Competicion){

            }
            if (best.competiciones[i]==""){
                best.competiciones[i]=carga.Competicion;
                best.partidos[i*5]=carga;
            }
        }
        
        cupholder.add(carga);
    }
    clock_t end = clock();
    archivo.close();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;

    return 0;
}
