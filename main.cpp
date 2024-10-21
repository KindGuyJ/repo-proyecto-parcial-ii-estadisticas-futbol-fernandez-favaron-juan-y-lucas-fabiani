#include"libreria.h"

int main(){
    ALMACEN almacen;
    string linea;
    ifstream archivo("Base_Datos_COMA.csv");
    Estadisticas estadisticas_totales;
    getline(archivo,linea);
    

    int idx=0;
    while (getline(archivo, linea)) {
        // Carga del archivo por linea a un struct partido
        stringstream stream(linea);
        PARTIDO carga;
        string temp;
        getline(stream,carga.jornada,',');
        getline(stream,temp,',');
        carga.fecha = temp;
        getline(stream,carga.equipolocal,',');
        getline(stream,temp,',');
        carga.goleslocales = stoi(temp);
        getline(stream,temp,',');
        carga.golesvisitantes = stoi(temp);
        getline(stream,carga.equipovisitante,',');
        getline(stream,carga.competicion,',');
        // Calculos
        almacen.agregar(carga); 
        estadisticas_totales.Ingresar(carga,idx); //se puede usar almacen.last() en vez de c pero esto deberia ser mas rapido que llamar a una funcion
        idx++; 
    }

    estadisticas_totales.Calculofinal();
    archivo.close();

    //Ejemplo de consulta
    string a,b;
    cout<<"Ingresar equipo,competencia a consultar"<<endl;
    getline(cin,a);
    getline(cin,b);
    estadisticas_totales.print(a,b);
    almacen.printlista(estadisticas_totales.PARTIDOs(a,b));
}