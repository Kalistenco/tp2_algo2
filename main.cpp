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
	Coordenadas partida("-58.4249824", "-34.5717485");
	Coordenadas llegada("-58.4618081", "-34.5680506");
	caba.verRecorridoDirecto(partida, llegada);
	caba.verRecorridoConCombinacion(partida, llegada);



	return 0;
}
