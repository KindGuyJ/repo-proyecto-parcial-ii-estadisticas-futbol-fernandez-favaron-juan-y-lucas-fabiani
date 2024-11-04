#include "libreria.h"
#include "csv.h"
#include <regex> // para verificar DD/MM/YYYY

using namespace std;

vector<Partido> partidos;
Estadisticas estadisticas_totales;

string input(const string &msg)
{
    cout << msg;
    string value;
    getline(cin, value); // Lee toda la línea
    return value;        // Retorna el valor leído
}

// para hacer print en main...
vector<Partido> traerPartidos(vector<int> lista)
{
    // filtrar en main o otra funcion mas
    vector<Partido> nuevo;
    for (int i = 0; i < lista.size(); i++)
    {
        nuevo.push_back(partidos[lista[i]]);
    }
    return nuevo;
}

void mostrarMenu()
{
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

void cargarArchivo()
{
    partidos.resize(0);
    estadisticas_totales = Estadisticas();

    ifstream archivo("Base_Datos_COMA.csv");
    string linea;
    getline(archivo, linea);

    int idx = 0;
    while (getline(archivo, linea))
    {
        // Carga del archivo por linea a un struct partido
        stringstream stream(linea);
        Partido partido;
        string temp;
        getline(stream, partido.jornada, ',');
        getline(stream, temp, ',');
        partido.fecha = temp;
        getline(stream, partido.equipolocal, ',');
        getline(stream, temp, ',');
        partido.goleslocales = stoi(temp);
        getline(stream, temp, ',');
        partido.golesvisitantes = stoi(temp);
        getline(stream, partido.equipovisitante, ',');
        getline(stream, partido.competicion, ',');

        // Calculos
        partidos.push_back(partido);
        estadisticas_totales.Ingresar(partido, idx); // se puede usar .last() en vez de idx pero esto deberia ser mas rapido que llamar a una funcion
        idx++;
    }

    estadisticas_totales.Calculofinal();
    archivo.close();
}

void EquipoValido(string &op1, string &op2, string &op3)
{
    do
    {   
        cout << "Ingresar: [(nombre del equipo) y (nombre de la competencia)] a eliminar." << endl;
        getline(cin, op1);
        size_t pos = op1.find(" y ");
        if (pos != string::npos)
        {
            // Extraer el nombre del equipo y de la competencia
            op2 = op1.substr(0, pos);
            op3 = op1.substr(pos + 3); // `+ 3` para saltar " y "
            if (estadisticas_totales.EquipoyCompetenciaExiste(op2 + op3))
            {
                return;
            }
            else
            {
                cout << "No se encontro ese equipo (" << op2 << ") en esa competencia (" << op3 << ")\n";
            }
        }
        else
        {
            cout << "Formato incorrecto. Asegúrese de usar el formato '[equipo] y [competencia]'.\n";
        }
    } while (true);
}

int ElegirPartido(string &op1, string &op2, string &op3)
{
    EquipoValido(op1, op2, op3);
    int op;
    vector<Partido> eleccion = traerPartidos(estadisticas_totales.getPartidosPor(op2, op3));
    cout << "Ingrese el numero del partido que desee modificar/eliminar:\n";
    eleccion[0].printHeaders();
    for (int i=0; i < eleccion.size(); i++)
    {
        cout << i << " - ";
        eleccion[i].printRow();
        cout << endl;
    }
    do
    {
        cin >> op;
        if (op > 0 && op < eleccion.size())
        {
            cout << "Fuera de rango. Intente nuevamente\n";
        }
    } while (op > 0 && op < eleccion.size());
    return estadisticas_totales.getPartidosPor(op2, op3)[op];
}
// Imprime vectores guardados en el objecto si sus posiciones coinciden con los valores de la lista
void printlista(vector<int> lista)
{
    // If se ejecuta si no encuentra ningun partido
    if (lista.size() == 0)
    {
        return;
    }

    cout << "Partidos jugados: " << endl;
    Partido::printHeaders();
    for (int i = 0; i < lista.size(); i++)
    {
        partidos[lista[i]].printRow();
    }
}

bool esFechaValida(const string &fecha)
{
    // Verificar formato DD/MM/YYYY
    regex formatoFecha(R"(\d{2}/\d{2}/\d{4})");
    return regex_match(fecha, formatoFecha);
}

string novacia(const string &mensaje)
{
    string entrada;
    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);
        if (!entrada.empty())
            break; // Aseguramos que no sea vacío
        cout << "Entrada no puede estar vacía. Por favor intente de nuevo." << endl;
    }
    return entrada;
}

Partido validarExistente(Partido nuevo)
{
    int op;
    string input;

    cout << "Elija qué campo desea modificar:\n";
    cout << "1. Jornada\n";
    cout << "2. Equipo local\n";
    cout << "3. Equipo visitante\n";
    cout << "4. Goles del equipo local\n";
    cout << "5. Goles del equipo visitante\n";
    cout << "6. Fecha (DD/MM/YYYY)\n";
    cout << "7. Competencia\n";
    cout << "Ingrese el número de la opción que desea modificar (0 para salir): ";
    cin >> op;
    cin.ignore(); // Ignorar el salto de línea residual en el buffer

    while (op != 0)
    {
        switch (op)
        {
        case 1:
            nuevo.jornada = novacia("Ingrese una jornada: ");
            break;
        case 2:
            nuevo.equipolocal = novacia("Ingrese el equipo local: ");
            break;
        case 3:
            nuevo.equipovisitante = novacia("Ingrese el equipo visitante: ");
            break;
        case 4:
            while (true)
            {
                input = novacia("Ingrese los goles del equipo local: ");
                if (input.size() > 0 && stoi(input) > -1)
                {
                    nuevo.goleslocales = stoi(input);
                    break;
                }
                else
                {
                    cout << "Entrada inválida. Por favor ingrese un número." << endl;
                }
            }
            break;
        case 5:
            while (true)
            {
                input = novacia("Ingrese los goles del equipo visitante: ");
                if (input.size() > 0 && stoi(input) > -1)
                {
                    nuevo.golesvisitantes = stoi(input);
                    break;
                }
                else
                {
                    cout << "Entrada inválida. Por favor ingrese un número." << endl;
                }
            }
            break;
        case 6:
            while (true)
            {
                input = novacia("Ingrese la fecha (DD/MM/YYYY): ");
                if (esFechaValida(input))
                {
                    nuevo.fecha = input;
                    break;
                }
                else
                {
                    cout << "Formato de fecha inválido. Por favor use DD/MM/YYYY." << endl;
                }
            }
            break;
        case 7:
            nuevo.competicion = novacia("Ingrese el nombre de la competencia: ");
            break;
        default:
            cout << "Opción inválida. Por favor, elija una opción válida.\n";
            break;
        }

        // Preguntar nuevamente para otra modificación o salida
        cout << "\n¿Desea modificar otro campo? Ingrese el número de la opción (0 para salir): ";
        cin >> op;
        cin.ignore(); // Ignorar el salto de línea residual en el buffer
    }

    return nuevo;
}

Partido validar()
{
    Partido nuevo;
    string input;

    nuevo.jornada = novacia("Ingrese una jornada: ");
    nuevo.equipolocal = novacia("Ingrese el equipo local: ");
    nuevo.equipovisitante = novacia("Ingrese el equipo visitante: ");

    // Validación de goles del equipo local
    while (true)
    {
        input = novacia("Ingrese los goles del equipo local: ");
        if (input.size() > 0 && stoi(input) > -1)
        {
            nuevo.goleslocales = stoi(input);
            break;
        }
        else
        {
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
        }
    }

    // Validación de goles del equipo visitante
    while (true)
    {
        input = novacia("Ingrese los goles del equipo visitante: ");
        if (input.size() > 0 && stoi(input) > -1)
        {
            nuevo.golesvisitantes = stoi(input);
            break;
        }
        else
        {
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
        }
    }

    // Validación de fecha
    while (true)
    {
        string fecha = novacia("Ingrese la fecha (DD/MM/YYYY): ");
        if (esFechaValida(fecha))
        {
            nuevo.fecha = fecha;
            break;
        }
        else
        {
            cout << "Formato de fecha inválido. Por favor use DD/MM/YYYY." << endl;
        }
    }

    nuevo.competicion = novacia("Ingrese el nombre de la competencia: ");

    return nuevo;
}

int main()
{
    cargarArchivo();
    string op1, op2, op3, nombreEquipo;

    int opcion;
    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            cout << "Ingrese el nombre de la competencia que desea consultar:\n";
            getline(cin, op1);
            estadisticas_totales.printcompetencia(op1);
            break;
        case 2:
            cout << "Imprimiendo todas las competencias: \n";
            estadisticas_totales.printtodascompetencias();
            break;

        case 3:
            cout << "Ingresar: [(nombre del equipo) y (nombre de la competencia)] a consultar." << endl;
            getline(cin, op1);
            EquipoValido(op1, op2, op3);
            estadisticas_totales.print(op2, op3);
            break;

        case 4:
            cout << "Ingresar: [(nombre del equipo) y (nombre de la competencia)] a consultar." << endl;
            getline(cin, op1);
            EquipoValido(op1, op2, op3);
            printlista(estadisticas_totales.getPartidosPor(op2, op3));
            break;

        case 5:
            estadisticas_totales.MasGolesCompeticion();
            break;

        case 6:
            estadisticas_totales.MejorYPeorEquipo();
            break;

        case 7:
            agregarRegistro(validar());
            cargarArchivo();
            break;

        case 8:
            eliminarRegistro(ElegirPartido(op1, op2, op3));
            cargarArchivo();
            break;

        case 9:
        {

            int op4 = ElegirPartido(op1, op2, op3);
            modificarRegistro(op4, validarExistente(partidos[op4]));
            cargarArchivo();
        }
        break;

        case 10:
        {
            string equipo = input("Equipo: ");
            cout << "Ingresa las dos fechas (DD/MM/YYYY): " << endl;
            string fecha = input("Desde: ");
            cout << fecha << endl;
            FECHA desde(fecha);
            fecha = input("Hasta: ");
            FECHA hasta(fecha);

            unordered_set comp = estadisticas_totales.CualesCompetencias();
            for (const auto &competencia : comp)
            {
                cout << "Competencia: " << competencia << endl;
                Partido::printHeaders();
                vector<Partido> filtrar = traerPartidos(estadisticas_totales.getPartidosPor(equipo, competencia));
                for (const Partido &elemento : filtrar)
                {
                    if (desde < elemento.fecha && elemento.fecha < hasta)
                    {
                        elemento.printRow();
                    }
                }
            }
        }
        break;

        case 11:
        {
            string equipo1 = input("Equipo 1: "),
                   equipo2 = input("Equipo 2: ");
            unordered_set comp = estadisticas_totales.CualesCompetencias();
            for (const auto &competencia : comp)
            {
                estadisticas_totales.Goles(equipo1, competencia);
                estadisticas_totales.Goles(equipo2, competencia);
            }
        }
        break;

        case 12:
        {
            int victorias1 = 0,
                victorias2 = 0,
                contras = 0,
                empates = 0;

            string equipo1 = input("Equipo 1: "),
                   equipo2 = input("Equipo 2: ");

            for (const Partido &partido : partidos)
            {
                string local = partido.equipolocal,
                       visita = partido.equipovisitante;
                int goleslocal = partido.goleslocales,
                    golesvisita = partido.golesvisitantes;

                if (local == equipo1 && visita == equipo2)
                {
                    contras++;
                    if (goleslocal > golesvisita)
                    {
                        victorias1++;
                    }
                    else if (goleslocal < golesvisita)
                    {
                        victorias2++;
                    }
                    else
                    {
                        empates++;
                    }
                }
                else if (local == equipo2 && visita == equipo1)
                {
                    contras++;
                    if (goleslocal > golesvisita)
                    {
                        victorias2++;
                    }
                    else if (goleslocal < golesvisita)
                    {
                        victorias1++;
                    }
                    else
                    {
                        empates++;
                    }
                }
            }
            cout << "Partidos entre ellos: " << contras<<endl;
            cout << "Partido empatados: " << empates<<endl;
            cout << "Equipo con mas victorias " << ((victorias1 > victorias2) ? equipo1 : equipo2)<<endl;
            cout << endl;
        }
        break;

        case 13:
        {
            int umbral;
            cout<<"Ingrese el umbral: \n";
            cin>>umbral;
            cin.ignore();
            bool esMaximo = (input("Como maximo (M) o minimo (otra cosa)? ") == "M") ? true : false;
            estadisticas_totales.printEstadisticasEquipos(umbral, esMaximo);
        }
        break;

        case 0:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
            break;
        };

        // Para separar interacciones del menu
        string r;
        cout << "Continuar? (s/n) ";
        getline(cin, r);
        if (r == "si" || r == "s" || r == "")
            continue;
        else if (r == "no" || r == "n")
            break;

    } while (opcion != 0);

    return 0;
}
