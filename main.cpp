/*
 * main.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include <iostream>
#include "Ciudad.h"
using namespace std;
int main(){

	// cck -34.602945, -58.370546
	// independencia y entre rios -34.618029, -58.391618
	// san juan y entre rios -34.623508, -58.391415
	// estacion angel gallardo -34.602105, -58.430768
	// plaza italia -34.581408, -58.421443

	Ciudad caba;
	Coordenadas llegada("-58.421443", "-34.581408");
	Coordenadas partida("-58.370546", "-34.602945");
	caba.verRecorridoDirecto(partida, llegada);
	caba.verRecorridoConCombinacion(partida, llegada);



	return 0;
}
