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
	 
	//plaza de mayo -34.608349, -58.372704
	//teatro colon -34.600754, -58.382832
	//plaza italia -34.581518, -58.421499
	//retiro -34.592717, -58.375580
	//belgrabo r -58.4618081,-34.5680506

	Coordenadas * usuario = new Coordenadas ("-58.382832","-34.600754");
	Coordenadas * usuario2 = new Coordenadas ("-58.375580","-34.592717");

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
			std::cout<<colecIterado->verUbicacionLongitud()<<colecIterado->verUbicacionLatitud()<<std::endl;
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
