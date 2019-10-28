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
/*Hay que modularizar todo este metodo*/
Lista<Tren*> Ciudad::recorridoDirectoTren(){
	/*cambiar el pedido de coordenadas de origen y destino*/
	Coordenadas origen=this->pedirOrigen();
	Coordenadas destino=this->pedirDestino();
	Lista<Tren*> recorrido;
	Lista<Tren*> estacionesOrigen;
	Lista<Tren*> estacionesDestino;
	/*busca las estaciones por condicion de distancia*/
	this->estacionesTren->iniciarCursor();
	while(this->estacionesTren->avanzarCursor()){
		Tren* estacionIterada=estacionesTren->obtenerCursor();
		Coordenadas * ubicacionEstacion=estacionIterada->verUbicacion();
		if(ubicacionEstacion->distanciaMetros(origen) < 500) {
			estacionesOrigen.agregar(estacionIterada);
		}
		else if(ubicacionEstacion->distanciaMetros(destino) < 500){
			estacionesDestino.agregar(estacionIterada);
		}
	}
	/*verifica si hay coincidecia de ramal para todas las estaciones de tren de origen y destino. Por ej
	lee un registro de origen e itera completamente por los de destino. Si encuentra coinidencia
	de ramal termina el recorrido y sigue abajo imprimiendo. Si no encuentra, avanza en la
	lista origen y hace el mismo procedimiento*/
	estacionesOrigen.iniciarCursor();
	estacionesDestino.iniciarCursor();
	bool recorridoEncontrado =false;
	while(estacionesOrigen.avanzarCursor()&&!recorridoEncontrado){
		Tren* estacionIteradaOrigen=estacionesOrigen.obtenerCursor();
		while(estacionesDestino.avanzarCursor()){
			Tren* estacionIteradaDestino=estacionesDestino.obtenerCursor();
			if(estanEnElMismoRamal(estacionIteradaOrigen, estacionIteradaDestino)){
				recorridoEncontrado=true;
				recorrido.agregar(estacionIteradaOrigen);
				recorrido.agregar(estacionIteradaDestino);
			}
		}

	}
/*imprime la lista recorrido, hay que llevarlo a otro metodo*/
	recorrido.iniciarCursor();
		while(recorrido.avanzarCursor()){
			Tren* estacion=recorrido.obtenerCursor();
			std::cout<<estacion->verRamal()<<estacion->verUbicacionLatitud()
					<<estacion->verUbicacionLongitud()<<
					estacion->verNombre()<<std::endl;
		}
	return recorrido;

}

bool Ciudad::estanEnElMismoRamal(Tren* origen, Tren* destino){

	return origen->verRamal()==destino->verRamal();
}
/*arreglar estos metodos con una entrada de datos para hacer pruebas de recorridos*/
Coordenadas Ciudad::pedirOrigen(){
	/*longitud, latitud*/
	Coordenadas origenUsuario("-58.4249824", "-34.5717485");
	return origenUsuario;
}
Coordenadas Ciudad::pedirDestino(){
	Coordenadas origenUsuario("-58.4618081", "-34.5680506");
		return origenUsuario;
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


