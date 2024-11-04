#include"libreria.h"

void mostrarMenu() {
    cout << "===============================" << endl;
    cout << "     MENU DE CONSULTAS         " << endl;
    cout << "===============================" << endl;
    cout << "1. Mostrar las estadisticas de una competencia" << endl;
    cout << "2. Mostrar las estadisticas de todas las competencias" << endl;
    cout << "3. Mostrar estadisticas de un equipo en una competicion" << endl;
    cout << "4. Consultar partidos de un equipo en una competicion" << endl;
    cout << "5. Competición con más goles convertidos" << endl;
    cout << "6. Equipo con más y menos goles convertidos en todas las competiciones" << endl; 
    cout << "7. Agregar un partido" << endl;
    cout << "8. Eliminar un partido" << endl;
    cout << "9. Modificar un partido" << endl;
    cout << "10. Consultar resultados de un equipo entre dos fechas" << endl;
    cout << "11. Comparar rendimiento general entre dos equipos" << endl;
    cout << "12. Comparar rendimiento particular entre dos equipos (enfrentamientos directos)" << endl;
    cout << "13. Filtrar equipos por umbral de goles promedio por partido" << endl;
    cout << "0. Salir" << endl;
    cout << "===============================" << endl;
    cout << "Seleccione una opción: ";
}

void CargaArchivo(ALMACEN &almacen, Estadisticas &estadisticas_totales)
{
    ifstream archivo("Base_Datos_COMA.csv");
    string linea;
    getline(archivo, linea);

    int idx = 0;
    while (getline(archivo, linea))
    {
        // Carga del archivo por linea a un struct partido
        stringstream stream(linea);
        PARTIDO carga;
        string temp;
        getline(stream, carga.jornada, ',');
        getline(stream, temp, ',');
        carga.fecha = temp;
        getline(stream, carga.equipolocal, ',');
        getline(stream, temp, ',');
        carga.goleslocales = stoi(temp);
        getline(stream, temp, ',');
        carga.golesvisitantes = stoi(temp);
        getline(stream, carga.equipovisitante, ',');
        getline(stream, carga.competicion, ',');
        // Calculos
        almacen.agregar(carga);
        estadisticas_totales.Ingresar(carga, idx); // se puede usar almacen.last() en vez de c pero esto deberia ser mas rapido que llamar a una funcion
        idx++;
    }

    estadisticas_totales.Calculofinal();
    archivo.close();
}

int main(){
    ALMACEN almacen;
    Estadisticas estadisticas_totales;
    CargaArchivo(almacen, estadisticas_totales);
    string op1,op2,op3;

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            cout<<"Ingrese el nombre de la competencia que desea consultar:\n";
            getline(cin,op1);
            estadisticas_totales.printcompetencia(op1);
            break;
        case 2:
            cout<<"Imprimiendo todas las competencias: \n";
            estadisticas_totales.printtodascompetencias();
            break;

        case 3:
            cout<<"Ingresar: [(nombre del equipo) y (nombre de la competencia)] a consultar."<<endl;
            getline(cin,op1);
            do{
                size_t pos = op1.find(" y ");
                if (pos != string::npos) {
                    // Extraer el nombre del equipo y de la competencia
                    op2 = op1.substr(0, pos);
                    op3 = op1.substr(pos + 3); // `+ 3` para saltar " y "
                    break;
                } else {
                    cout << "Formato incorrecto. Asegúrese de usar el formato '[equipo] y [competencia]'.\n";
            }} while (true);
                
            estadisticas_totales.print(op2,op3);
            break;

        case 4:
            cout<<"Ingresar: [(nombre del equipo) y (nombre de la competencia)] a consultar."<<endl;
            getline(cin,op1);
            do{
                size_t pos = op1.find(" y ");
                if (pos != string::npos) {
                    // Extraer el nombre del equipo y de la competencia
                    op2 = op1.substr(0, pos);
                    op3 = op1.substr(pos + 3); // `+ 3` para saltar " y "
                    break;
                } else {
                    cout << "Formato incorrecto. Asegúrese de usar el formato '[equipo] y [competencia]'.\n";
            }} while (true);
                
            almacen.printlista(estadisticas_totales.PARTIDOs(op2,op3));
            break;

        case 5:
            estadisticas_totales.MasGolesCompeticion();
            break;
        
        case 6:
            estadisticas_totales.MejorYPeorEquipo();
            break;
        
        case 7:
            break;
        
        case 8:
            break;

        case 9:
            break;
        
        case 10:
            break;

        case 11:
            break;
        
        case 12:
            break;

        case 13:
            break;

        case 0:
            cout<<"Saliendo..."<<endl;
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
            break;
        };
    } while(opcion != 0);

    //Ejemplo de consulta
    string a,b;

    almacen.printlista(estadisticas_totales.PARTIDOs(a,b));
    return 0;
}
