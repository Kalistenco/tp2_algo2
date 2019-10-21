/*
 * Ciudad.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include "Ciudad.h"


Ciudad::Ciudad(){

	this->estacionesTren=new Lista<Tren*>;
	this->bocasSubte=new Lista<Subte*>;
	this->estacionesColectivo=new Lista<Colectivo*>;

	Archivo trenes(ARCHIVO_TRENES);
	Lista<std::string> registrosEstacionesTren;
	trenes.leerArchivo(registrosEstacionesTren);
	Archivo colectivos(ARCHIVO_COLECTIVOS);
	Lista<std::string> registrosEstacionesColectivo;
	colectivos.leerArchivo(registrosEstacionesColectivo);
	Archivo subtes(ARCHIVO_SUBTES);
	Lista<std::string> registrosBocasSubte;
	subtes.leerArchivo(registrosBocasSubte);

	/*Recorrido y carga de registros en listas*/

	registrosEstacionesTren.iniciarCursor();

	while(registrosEstacionesTren.avanzarCursor()){
		std::string infoEstacion=registrosEstacionesTren.obtenerCursor();
		Tren* nuevaEstacion=new Tren(infoEstacion);
		this->estacionesTren->agregar(nuevaEstacion);
	}

	registrosBocasSubte.iniciarCursor();

	while(registrosBocasSubte.avanzarCursor()){
		std::string infoEstacion=registrosBocasSubte.obtenerCursor();
		Subte* nuevaEstacion=new Subte(infoEstacion);
		this->bocasSubte->agregar(nuevaEstacion);
	}

	registrosEstacionesColectivo.iniciarCursor();

	while(registrosEstacionesColectivo.avanzarCursor()){
		std::string infoEstacion=registrosEstacionesColectivo.obtenerCursor();
		Colectivo* nuevaEstacion=new Colectivo(infoEstacion);
		this->estacionesColectivo->agregar(nuevaEstacion);
	}

}

Ciudad::~Ciudad(){

	this->bocasSubte->iniciarCursor();

	while(bocasSubte->avanzarCursor()){
		delete this->bocasSubte->obtenerCursor();
	}

	this->estacionesColectivo->iniciarCursor();

	while(this->estacionesColectivo->avanzarCursor()){
		delete this->estacionesColectivo->obtenerCursor();
	}

	this->estacionesTren->iniciarCursor();

	while(this->estacionesTren->avanzarCursor()){
		delete this->estacionesTren->obtenerCursor();
	
	}
	
	delete this->bocasSubte;
	delete this->estacionesColectivo;
	delete this->estacionesTren;
}


