/*
 * Menu.cpp
 *
 *  Created on: 29 oct. 2019
 *      Author: David
 */
#include<iostream>
#include"Menu.h"
#include "Coordenadas.h"
#include <string>
using namespace std;


Menu::Menu(){
	miCiudad = new Ciudad();
}

void Menu::iniciarMenu(){

	string auxLatitudOrigen,auxLatitudDestino,auxLongitudOrigen,auxLongitudDestino;
	char opcionMenu ;
	bool salir = false;

	cout<<"   -- CIUDAD DIGITAL EN MOVIMIENTO V1.0 --"<<endl;
	cout<<""<<endl;

	while(salir != true){

		cout<<""<<endl;
		cout<<"  ELIJA TIPO DE RECORIDO  "<<endl;
		cout<<""<<endl;
		cout<<"1 - Recorrido sin conbinaciones"<<endl;
		cout<<"2 - Recorrido con conbinaciones"<<endl;
		cout<<"0 - salir"<<endl;
		cout<<""<<endl;
		cout <<"Ingrese su opcion: ";
		cin>>opcionMenu;
		cout <<""<<endl;
		//opcionMenu = this->opcionValida(0,2);

		if(opcionMenu=='1' || opcionMenu=='2'){

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
		}
		Coordenadas origen(auxLongitudOrigen,auxLatitudOrigen);
		Coordenadas destino(auxLongitudDestino,auxLatitudDestino);

		switch (opcionMenu){
			case '0':
				cout<<"\n PROGRAMA FINALIZADO "<<endl;
				salir = true;
			break;
			case '1':
				cout<<""<<endl;
				cout<<" RECORRIDO SIN CONBINACIONES "<<endl;
				cout<<""<<endl;
				this->miCiudad->verRecorridoDirecto(origen,destino);
				cout<<""<<endl;
			break;
			case '2':
				cout<<""<<endl;
				cout<<" RECORRIDO CON CONBINACIONES "<<endl;
				cout<<""<<endl;
				this->miCiudad->verRecorridoConCombinacion(origen,destino);
				cout<<""<<endl;
			break;

			default:
				cout<<" OPCION NO VALIDA, INGRESE DE NUEVO SU OPCION "<<endl;
		}
	}
}

Menu::~Menu(){
	delete this->miCiudad;
}



