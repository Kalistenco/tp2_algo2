/*
 * main.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include <iostream>
#include "Ciudad.h"

int main(){
	Ciudad miCiudad;
	Lista<Tren*> *estaciones=miCiudad.verEstacionesTren();
	
	estaciones->iniciarCursor();
	/*de prueba para ver la carga de archivos*/
	while(estaciones->avanzarCursor()){
			estaciones->obtenerCursor()->verRamal();
	}

	return 0;
}