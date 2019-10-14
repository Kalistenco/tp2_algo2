/*
 * Ciudad.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include "Ciudad.h"

Ciudad::Ciudad(){
	this->estacionesTren=new Lista<Estacion*>;
	this->bocasSubte=new Lista<Estacion*>;
	this->estacionesMetrobus=new Lista<Estacion*>;

	Archivo trenes("estaciones-de-ferrocarril.csv");
	Lista<std::string> *estacionesTren=trenes.leerArchivo();
	Archivo metrobus("estaciones-de-metrobus.csv");
	Lista<std::string> *estacionesMetrobus=metrobus.leerArchivo();
	Archivo subte("bocas-de-subte.csv");
	Lista<std::string> *bocasSubte=subte.leerArchivo();

/*la comparacion por tipo de transporte queda mal sin tener clase por cada transporte*/
	estacionesTren->iniciarCursor();
	while(estacionesTren->avanzarCursor()){
		std::string infoEstacion=estacionesTren->obtenerCursor();
		Estacion* nuevaEstacion=new Estacion(infoEstacion,"ferrocarril");
		this->estacionesTren->agregar(nuevaEstacion);
	}
	bocasSubte->iniciarCursor();

	while(bocasSubte->avanzarCursor()){
		std::string infoEstacion=estacionesMetrobus->obtenerCursor();
		Estacion* nuevaEstacion=new Estacion(infoEstacion, "subte");
		this->bocasSubte->agregar(nuevaEstacion);
	}
	estacionesMetrobus->iniciarCursor();

	while(estacionesMetrobus->avanzarCursor()){
		std::string infoEstacion=estacionesMetrobus->obtenerCursor();
		Estacion* nuevaEstacion=new Estacion(infoEstacion, "metrobus");
		this->estacionesMetrobus->agregar(nuevaEstacion);
	}
	delete estacionesTren;
	delete bocasSubte;
	delete estacionesMetrobus;
}
Ciudad::~Ciudad(){
	this->bocasSubte->iniciarCursor();
	while(bocasSubte->avanzarCursor()){
		delete this->bocasSubte->obtenerCursor();
	}
	this->estacionesMetrobus->iniciarCursor();
	while(this->estacionesMetrobus->avanzarCursor()){
		delete this->estacionesMetrobus->obtenerCursor();
	}
	this->estacionesTren->iniciarCursor();
		while(this->estacionesTren->avanzarCursor()){
			delete this->estacionesTren->obtenerCursor();
		}
	delete this->bocasSubte;
	delete this->estacionesMetrobus;
	delete this->estacionesTren;


}


