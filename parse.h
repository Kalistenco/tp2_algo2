#ifndef PARSE__H
#define PARSE__H

#include <iostream>
#include <fstream>

using namespace std;

// esta función se encarga abrir un archovo y de guardar en memoria sus registros
// los registros se guardan en un vector de strings
void parseFile (fstream &, vector <string> &);

#endif