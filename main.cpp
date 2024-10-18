#include"libreria.h"
#include <sstream> //para stream

int main(){
    dataclass cupholder;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    Stats allstats;
    getline(archivo,linea);
    
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
        c++; //se puede usar cupholder.last() pero esto deberia ser mas rapido que llamar a una funcion...    }
    }

    allstats.Calculofinal();
    archivo.close();

    //Ejemplo de consulta
    string a,b;
    cout<<"Ingresar equipo,competencia a consultar"<<endl;
    getline(cin,a);
    getline(cin,b);
    allstats.print(a,b);
    cupholder.printlista(allstats.partidos(a,b));
}