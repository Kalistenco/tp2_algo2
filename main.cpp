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
	 
	Coordenadas * usuario = new Coordenadas ("-34.609590","-58.391866");
	Coordenadas * usuario2 = new Coordenadas ("-34.581311","-58.421445");

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
			std::cout<<colecIterado->verLinea()<<std::endl;
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
