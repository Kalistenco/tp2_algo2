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

	Lista<Tren*>*trenes=caba.verEstacionesTren();
	cout.precision(10);
	trenes->iniciarCursor();
	while(trenes->avanzarCursor()){
		Tren * trenIterado=trenes->obtenerCursor();
		std::cout<<trenIterado->verRamal()<<std::endl;
	}
	
	Lista<Colectivo*>*colectivos=caba.verColectivos();
	cout.precision(10);
	colectivos->iniciarCursor();
	while(colectivos->avanzarCursor()){
		Colectivo * colecIterado=colectivos->obtenerCursor();
		std::cout<<colecIterado->verUbicacionLatitud()<<" | "<<
		colecIterado->verUbicacionLongitud()<<" | "<<colecIterado
		->verLinea()<<std::endl;
	}
	Lista<Subte*>*subtes=caba.verBocasSubte();
	cout.precision(10);
	subtes->iniciarCursor();
		while(subtes->avanzarCursor()){
			Subte * subIterado=subtes->obtenerCursor();
			std::cout<<subIterado->verUbicacionLatitud()<<" | "<<
			subIterado->verUbicacionLongitud()<<" | "<<subIterado
			->verLinea()<<" | "<<subIterado->verCombinaciones()<<std::endl;
	}
	
	
	
	
	return 0;
}
