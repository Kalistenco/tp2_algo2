/*
 * Ciudad.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include "Ciudad.h"
#include "util.h"
#include "Colectivo.h"
#include "Subte.h"
#include "Tren.h"

Ciudad::Ciudad(){

	this->estacionesTren=new Lista<Tren*>;
	this->bocasSubte=new Lista<Subte*>;
	this->estacionesColectivo=new Lista<Colectivo*>;

	Archivo trenes(ARCHIVO_TRENES);
	Lista<std::string> *registrosEstacionesTren=trenes.leerArchivo();

	Archivo colectivos(ARCHIVO_COLECTIVOS);
	Lista<std::string> *registrosEstacionesColectivo=colectivos.leerArchivo();

	Archivo subtes(ARCHIVO_SUBTES);
	Lista<std::string> *registrosBocasSubte=subtes.leerArchivo();

/*la comparacion por tipo de transporte queda mal sin tener clase por cada transporte*/
	registrosEstacionesTren->iniciarCursor();

	while(registrosEstacionesTren->avanzarCursor()){
		std::string infoEstacion=registrosEstacionesTren->obtenerCursor();
		Tren* nuevaEstacion=new Tren(infoEstacion);
		this->estacionesTren->agregar(nuevaEstacion);
	}

	registrosBocasSubte->iniciarCursor();

	while(registrosBocasSubte->avanzarCursor()){
		std::string infoEstacion=registrosBocasSubte->obtenerCursor();
		Subte* nuevaEstacion=new Subte(infoEstacion);
		this->bocasSubte->agregar(nuevaEstacion);
	}

	registrosEstacionesColectivo->iniciarCursor();

	while(registrosEstacionesColectivo->avanzarCursor()){
		std::string infoEstacion=registrosEstacionesColectivo->obtenerCursor();
		Colectivo* nuevaEstacion=new Colectivo(infoEstacion);
		this->estacionesColectivo->agregar(nuevaEstacion);
	}

	delete estacionesTren;
	delete bocasSubte;
	delete estacionesColectivo;
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


