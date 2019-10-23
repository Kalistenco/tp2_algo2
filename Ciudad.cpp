/*
 * Ciudad.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include <iostream>
#include "Ciudad.h"
#include "Coordenadas.h"
#include "Estacion.h"

Ciudad::Ciudad(){

	this->estacionesTren=new Lista<Estacion*>;
	this->bocasSubte=new Lista<Estacion*>;
	this->estacionesColectivo=new Lista<Estacion*>;

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
		Estacion* nuevaEstacion=new Estacion(infoEstacion, "ferrocarril");
		this->estacionesTren->agregar(nuevaEstacion);
	}

	registrosBocasSubte.iniciarCursor();

	while(registrosBocasSubte.avanzarCursor()){
		std::string infoEstacion=registrosBocasSubte.obtenerCursor();
		Estacion* nuevaEstacion=new Estacion(infoEstacion, "subte");
		this->bocasSubte->agregar(nuevaEstacion);
	}

	registrosEstacionesColectivo.iniciarCursor();

	while(registrosEstacionesColectivo.avanzarCursor()){
		std::string infoEstacion=registrosEstacionesColectivo.obtenerCursor();
		Estacion* nuevaEstacion=new Estacion(infoEstacion, "colectivo");
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


void Ciudad::verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*> * estacionesPartida;
	Lista<Estacion*> * estacionesLlegada;

	estacionesPartida = obtenerEstacionesCercanas (puntoPartida);
	estacionesLlegada = obtenerEstacionesCercanas (puntoLlegada);

	//testing

	std::cout<<"ESTACIONES PARTIDA"<<std::endl;

	estacionesPartida->iniciarCursor();

	while (estacionesPartida->avanzarCursor()){
		Estacion * estacionPrueba = estacionesPartida->obtenerCursor();
		std::cout<<estacionPrueba->verLinea()<<std::endl;
	}

	std::cout<<"ESTACIONES LLEGADA"<<std::endl;

	estacionesLlegada->iniciarCursor();

	while (estacionesLlegada->avanzarCursor()){
		Estacion * estacionPrueba2 = estacionesLlegada->obtenerCursor();
		std::cout<<estacionPrueba2->verLinea()<<std::endl;
	}

}

Lista<Estacion*>* Ciudad::obtenerEstacionesCercanas (Coordenadas ubicacionUsuario){
	Lista<Estacion*>* estacionesCercanas = new Lista<Estacion*>;
	
	this->estacionesTren->iniciarCursor();
	this->estacionesColectivo->iniciarCursor();
	this->bocasSubte->iniciarCursor();

	while(this->estacionesTren->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->estacionesTren->obtenerCursor()->verUbicacion();

		if(ubicacionEstacion->distanciaMetros(&ubicacionUsuario) < 500) {	
			//testing
			std::cout<<"agrego estacion de tren"<<std::endl;
			Estacion * trenIterado = this->estacionesTren->obtenerCursor();
			trenIterado->verLinea();
			estacionesCercanas->agregar(trenIterado);
		}
	}

	while(this->estacionesColectivo->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->estacionesColectivo->obtenerCursor()->verUbicacion();
	
		if(ubicacionEstacion->distanciaMetros(&ubicacionUsuario) < 500) {
			estacionesCercanas->agregar(this->estacionesColectivo->obtenerCursor());
		}
	}

	while(this->bocasSubte->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->bocasSubte->obtenerCursor()->verUbicacion();
	
		if(ubicacionEstacion->distanciaMetros(&ubicacionUsuario) < 500) {
			estacionesCercanas->agregar(this->bocasSubte->obtenerCursor());
		}
	}

	return estacionesCercanas;
}
