#include <iostream>
#include <fstream>

#include "parse.h"
#include "Lista.h"
#include "util.h"

using namespace std;

void parseFile (fstream & file, vector <string> & fields)
{
    string lineData;

    file.open (ESTACIONES_METROBUS_CSV, ios::in);

    while (!file.eof()) {
        getline (file, lineData);
        fields.push_back(lineData);
    }
}
