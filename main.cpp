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
		std::cout<<trenIterado->verUbicacionLatitud()<<" | "<<
		trenIterado->verUbicacionLongitud()<<std::endl;

	}

	return 0;
}
