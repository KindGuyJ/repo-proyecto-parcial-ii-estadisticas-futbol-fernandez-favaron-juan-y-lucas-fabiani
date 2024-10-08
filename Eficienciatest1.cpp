#include <ctime>
#include"libreria.h"
#include <sstream> //para stream
#include <iomanip>

using namespace std;

struct top5 {
    string competiciones[10];
    partido partidos[50];

    //No es lindo
    void best(partido x,int n){
        n=n*5;
        for(int i=n;i<n+5;i++){
            if ((x.GolesLocal+x.GolesVisitante)>=(partidos[i].GolesLocal+partidos[i].GolesVisitante)){
                partido t = partidos[i];
                partidos[i]=x;
                for (int j = i+1; j < n+5; j++)
                {
                    x = partidos[j];
                    partidos[j] = t;
                    t = x;
                }
                break;
            }
        }
    }
};

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
        for (int i = 0; i < 10; i++)
        {
            if (best.competiciones[i]==carga.Competicion){
                //Este if de abajo le saca 0.02 segundos
                if ((carga.GolesLocal+carga.GolesVisitante)>=(best.partidos[i*5+4].GolesLocal+best.partidos[i*5+4].GolesVisitante)){
                    best.best(carga,i);
                }
                break;
            }
            if (best.competiciones[i]==""){
                best.competiciones[i]=carga.Competicion;
                best.best(carga,i);
                break;
            }
        }
        
        cupholder.add(carga);
    }
    clock_t end = clock();
    archivo.close();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;

    //Feo como ninguno este imprimir
    for (int i = 0; i < 10; i++)
    {
        if (best.competiciones[i] == ""){break;}
        cout << endl <<"Competicion: " << best.competiciones[i] << endl;
        cout <<"Jornada                    \tFecha    \tEquipo Local                   \tEquipo Visitante            \tGoles Local\tGoles Visitante\n";
        for (int j = 5; j > 0; j--)
        {
            cout << setw(30) << best.partidos[i * 5 + j-1].Jornada << "\t"
                 << setw(15) << best.partidos[i * 5 + j-1].Fecha << "\t"
                 << setw(30) << best.partidos[i * 5 + j-1].EquipoLocal << "\t"
                 << setw(30) << best.partidos[i * 5 + j-1].EquipoVisitante << "\t"
                 << setw(10) << best.partidos[i * 5 + j-1].GolesLocal << "\t"
                 << setw(10) << best.partidos[i * 5 + j-1].GolesVisitante << "\n";
        }
    }
    return 0;
}
