#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// Convierte una linea Juan,16,Cordoba en vector ("Juan", "16", "Cordoba")

vector<string> splitString(const string& line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<map<string, string>> loadCSV(const string& filename) {
    ifstream file(filename);
    string line;
    vector<map<string, string>> data;
    vector<string> headers;

    if (getline(file, line)) {
        headers = splitString(line, ',');
    }

    while (getline(file, line)) {
        vector<string> values = splitString(line, ',');
        map<string, string> row;
        for (size_t i = 0; i < values.size(); i++) {
            row[headers[i]] = values[i];
        }
        data.push_back(row);
    }
    file.close();

    return data;
}

int main() {
    auto data = loadCSV("Base_Datos_COMA.csv");

    // Acceder al valor de la primera fila y la columna "Jornada"
    if (!data.empty()) {  // Verificar que el archivo no esté vacío
        cout << "Valor de la columna 'Jornada' en la primera fila: " << data[15]["Jornada"] << endl;
    } else {
        cout << "No se pudo cargar ningún dato del archivo CSV." << endl;
    }

    return 0;
}
