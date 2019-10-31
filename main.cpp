/*
 * main.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include <iostream>
#include "Ciudad.h"
#include "Menu.h"
using namespace std;
int main(){

	/*Ciudad caba;
	Coordenadas partida("-58.4249824", "-34.5717485");
	Coordenadas llegada("-58.4618081", "-34.5680506");
	caba.verRecorridoDirecto(partida, llegada);
	caba.verRecorridoConCombinacion(partida, llegada);*/

<<<<<<< HEAD
	Lista<Estacion*>*trenes=caba.verEstacionesTren();
	cout.precision(10);
	trenes->iniciarCursor();
	while(trenes->avanzarCursor()){
		Estacion * trenIterado=trenes->obtenerCursor();
		std::cout<<trenIterado->verNombre()<<std::endl;
	}
=======
	Menu miMenu;
	miMenu.iniciarMenu();
>>>>>>> 9ea4403ea98fe49371d37a5e2a8b87e69bcf1dd3

/*	Lista<Estacion*>*colectivos=caba.verColectivos();
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
			std::cout<<subIterado->verLinea()<<std::endl;
		}
*/
	return 0;
}
