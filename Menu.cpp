/*
 * Menu.cpp
 *
 *  Created on: 29 oct. 2019
 *      Author: David
 */
#include<iostream>
#include"Menu.h"
#include "Coordenadas.h"
using namespace std;
Menu::Menu(){
	miCiudad = new Ciudad();
}

void Menu::iniciarMenu(){

	string auxLatitudOrigen,auxLatitudDestino,auxLongitudOrigen,auxLongitudDestino;

	cout<<"   -- CIUDAD DIGITAL EN MOVIMIENTO V1.0 --"<<endl;

	cout<<"ORIGEN"<<endl;
	cout<<"   Ingrese longitud de origen: ";
	cin>>auxLongitudOrigen;
	cout<<"   Ingrese latitud de origen: ";
	cin>>auxLatitudOrigen;

	cout<<"DESTINO"<<endl;
	cout<<"   Ingrese longitud de destino: ";
	cin>>auxLongitudDestino;
	cout<<"   Ingrese latitud de destino: ";
	cin>>auxLatitudDestino;


	Coordenadas* origen = new Coordenadas(auxLongitudOrigen,auxLatitudOrigen);
	Coordenadas* destino = new Coordenadas(auxLongitudDestino,auxLatitudDestino);

	this->miCiudad->verRecorridoDirecto(*origen,*destino);

	delete origen;
	delete destino;
}





