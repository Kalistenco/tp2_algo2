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

	Ciudad caba;
	Coordenadas * usuario = new Coordenadas ("-58.997844","-34.5984003");
	Coordenadas * usuario2 = new Coordenadas ("-58.188026","-34.8332066");

	caba.verRecorridoDirecto(*usuario, *usuario2);


/*	Lista<Estacion*>*trenes=caba.verEstacionesTren();
	cout.precision(10);
	trenes->iniciarCursor();
	while(trenes->avanzarCursor()){
		Estacion * trenIterado=trenes->obtenerCursor();
		std::cout<<trenIterado->verLinea()<<std::endl;
			std::cout<<trenIterado->verLinea()<<std::endl;
	}

	Lista<Estacion*>*colectivos=caba.verColectivos();
	cout.precision(10);
	colectivos->iniciarCursor();
	while(colectivos->avanzarCursor()){
		Estacion * colecIterado=colectivos->obtenerCursor();
			std::cout<<colecIterado->verUbicacionLatitud()<<"|"<<colecIterado->verUbicacionLongitud()<<std::endl;
	}

	Lista<Estacion*>*subtes=caba.verBocasSubte();
	cout.precision(10);
	subtes->iniciarCursor();
		while(subtes->avanzarCursor()){
			Estacion * subIterado=subtes->obtenerCursor();
			std::cout<<subIterado->verUbicacionLatitud()<<"|"<<subIterado->verUbicacionLongitud()<<std::endl;
	}
*/		
	return 0;
}
