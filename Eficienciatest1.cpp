#include <ctime>
#include"libreria.h"
#include <sstream> //para stream
#include <iomanip>

using namespace std;

struct top5 {
    vector<string> competiciones;
    vector<vector<partido>> partidos;

    //Movido como funcion del struct
    void print(){
            for (int i = 0; i < competiciones.size(); i++)
    {
        if (competiciones[i] == "*"){break;}
        cout << endl <<"Competicion: " << competiciones[i] << endl;
        cout <<setw(25)<<"Jornada"<<setw(15)<<"\tFecha"<<setw(30)<<"\tEquipo Local"<<setw(30)<<"\tEquipo Visitante"<<setw(10)<<"\tGoles Local"<<setw(10)<<"\tGoles Visitante\n";
        for (int j = 5; j > 0; j--)
        {
            cout << setw(30) << partidos[i][j-1].Jornada << "\t"
                 << setw(15) << partidos[i][j-1].Fecha << "\t"
                 << setw(30) << partidos[i][j-1].EquipoLocal << "\t"
                 << setw(30) << partidos[i][j-1].EquipoVisitante << "\t"
                 << setw(10) << partidos[i][j-1].GolesLocal << "\t"
                 << setw(10) << partidos[i][j-1].GolesVisitante << "\n";
        }
    }
    }
    void best(partido x,int n){
        for(int i=0;i<5;i++){
            if ((x.GolesLocal+x.GolesVisitante)>=(partidos[n][i].GolesLocal+partidos[n][i].GolesVisitante)){
                partido t = partidos[n][i];
                partidos[n][i]=x;
                for (int j = i+1; j < 5; j++)
                {
                    x = partidos[n][j];
                    partidos[n][j] = t;
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
    best.competiciones.push_back("*");//Y te preguntaras porque no uso "" vacio y es porque en la base de datos hay competencias
                                      //que aparecen como ""
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
        for (int i = 0; i < best.competiciones.size(); i++)
        {
            if (best.competiciones[i]==carga.Competicion){
                //Este if de abajo le saca 0.02 segundos
                if ((carga.GolesLocal+carga.GolesVisitante)>=(best.partidos[i][4].GolesLocal+best.partidos[i][4].GolesVisitante)){
                    best.best(carga,i);
                }
                break;
            }
            if (best.competiciones[i]=="*"){
                best.competiciones[i]=carga.Competicion;
                best.competiciones.push_back("*");
                best.partidos.push_back({});
                best.partidos[i].push_back({});
                best.partidos[i].push_back({});
                best.partidos[i].push_back({});
                best.partidos[i].push_back({});
                best.partidos[i].push_back({});
                best.best(carga,i);
                break;
            }
        }
        
        cupholder.add(carga);
    }
    clock_t end = clock();

    archivo.close();
    best.print();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;
    //Tardo elapsed_secs: 0.007
    return 0;
}
