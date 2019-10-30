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

	this->estacionesTren = new Lista<Estacion*>;
	this->bocasSubte = new Lista<Estacion*>;
	this->estacionesColectivo = new Lista<Estacion*>;

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
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>  estacionesLlegada;
	Lista<Estacion*> recorridoDirecto;

	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, &estacionesLlegada);
	vincularPartidaLlegada(&estacionesPartida, &estacionesLlegada, &recorridoDirecto);

	//testing

	std::cout<<"ESTACIONES PARTIDA"<<std::endl;

	estacionesPartida.iniciarCursor();

	while (estacionesPartida.avanzarCursor()){
		Estacion * estacionPrueba = estacionesPartida.obtenerCursor();
		std::cout<<estacionPrueba->verNombre()<<std::endl;
	}

	std::cout<<"ESTACIONES LLEGADA"<<std::endl;

	estacionesLlegada.iniciarCursor();

	while (estacionesLlegada.avanzarCursor()){
		Estacion * estacionPrueba2 = estacionesLlegada.obtenerCursor();
		std::cout<<estacionPrueba2->verNombre()<<std::endl;
	}

	std::cout<<"RECORRIDO DIRECTO"<<std::endl;

	recorridoDirecto.iniciarCursor();

	while (recorridoDirecto.avanzarCursor()){
		Estacion * estacionPrueba3 = recorridoDirecto.obtenerCursor();
		std::cout<<estacionPrueba3->verNombre()<<std::endl;
	}


}


void Ciudad::obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,
		Lista<Estacion*>*estacionesCercanas){
	//Lista<Estacion*> estacionesCercanas = new Lista<Estacion*>;
	
	this->estacionesTren->iniciarCursor();
	this->estacionesColectivo->iniciarCursor();
	this->bocasSubte->iniciarCursor();

	while(this->estacionesTren->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->estacionesTren->obtenerCursor()->verUbicacion();

		if(ubicacionEstacion->distanciaMetros(ubicacionUsuario) < 250) {	
			Estacion * trenIterado = this->estacionesTren->obtenerCursor();
			estacionesCercanas->agregar(trenIterado);
		}
	}

	while(this->estacionesColectivo->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->estacionesColectivo->obtenerCursor()->verUbicacion();
	
		if(ubicacionEstacion->distanciaMetros(ubicacionUsuario) < 250) {
			Estacion * colectivoIterado = this->estacionesColectivo->obtenerCursor();
			estacionesCercanas->agregar(colectivoIterado);
		}

	}

	while(this->bocasSubte->avanzarCursor()){
		Coordenadas * ubicacionEstacion = this->bocasSubte->obtenerCursor()->verUbicacion();
	
		if(ubicacionEstacion->distanciaMetros(ubicacionUsuario) < 250) {
			Estacion * subteIterado = this->bocasSubte->obtenerCursor();
			estacionesCercanas->agregar(subteIterado);
		}
	}

	//return estacionesCercanas;
}

void Ciudad::vincularPartidaLlegada(Lista<Estacion*> * estacionesPartida, Lista<Estacion*> * estacionesLlegada,
		Lista<Estacion*>*recorridoDirecto){
	//Lista<Estacion*> * recorridoDirecto = new Lista<Estacion*>;

	estacionesPartida->iniciarCursor();

	while(estacionesPartida->avanzarCursor()){
		Estacion *estacionIterada=estacionesPartida->obtenerCursor();
		estacionesLlegada->iniciarCursor();
		while(estacionesLlegada->avanzarCursor()){
			Estacion* estacionLlegada=estacionesLlegada->obtenerCursor();
			if(estacionIterada->verLinea() == estacionLlegada->verLinea()){
				recorridoDirecto->agregar(estacionesPartida->obtenerCursor());
				recorridoDirecto->agregar(estacionesLlegada->obtenerCursor());
				break;
			}
		}

	}

	//return recorridoDirecto;
}

void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>  estacionesLlegada;
	Lista<Estacion*> recorridoDirecto;
	/*carga estaciones cercanas a los puntos dados por el usuario*/
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, &estacionesLlegada);
	bool recorridoDirectoEncontrado=false;

	estacionesLlegada.iniciarCursor();
	while(estacionesLlegada.avanzarCursor()&&!recorridoDirectoEncontrado){
		Estacion* estacionLlegada=estacionesLlegada.obtenerCursor();
		Coordenadas ubicacionEstacionIntermedia=estacionLlegada->verUbicacion();

		/*para un tipo de estacion de llegada busca las que sean del mismo tipo y sean de la misma linea
		 -ramal-etc. Para cada estacion con esas condiciones busca las estaciones cercanas y junto a las estaciones cercanas
		 a las de partida usa el mismo algoritmo del recorrido directo. Si lo encuentra corta el ciclo e imprime.*/

		if(estacionLlegada->verTipoTransporte()=="ferrocarril"){
			this->estacionesTren->iniciarCursor();
			while(estacionesTren->avanzarCursor()&&!recorridoDirectoEncontrado){
				Estacion* estacionIntermedia=estacionesTren->obtenerCursor();
				if(estacionIntermedia->verLinea()==estacionLlegada->verLinea()){
					Lista<Estacion*>  estacionesCercanasIntermedias;
					this->obtenerEstacionesCercanas(estacionIntermedia->verUbicacion(),
							&estacionesCercanasIntermedias);
					recorridoDirectoEncontrado=this->verRecorridoDirecto(estacionIntermedia->verUbicacion()
							,puntoPartida,
							&estacionesCercanasIntermedias,&estacionesPartida,&recorridoDirecto );

				}
			}
		}
		else if(estacionLlegada->verTipoTransporte()=="subte"){
			this->bocasSubte->iniciarCursor();
			while(bocasSubte->avanzarCursor()&&!recorridoDirectoEncontrado){
				Estacion* estacionIntermedia=bocasSubte->obtenerCursor();
				if(estacionIntermedia->verLinea()==estacionLlegada->verLinea()){
					Lista<Estacion*>  estacionesCercanasIntermedias;
					this->obtenerEstacionesCercanas(estacionIntermedia->verUbicacion(),
							&estacionesCercanasIntermedias);
					recorridoDirectoEncontrado=this->verRecorridoDirecto(estacionIntermedia->verUbicacion()
							,puntoPartida,
							&estacionesCercanasIntermedias,&estacionesPartida,&recorridoDirecto );
				}
			}


		}else if(estacionLlegada->verTipoTransporte()=="colectivo"){
			this->estacionesColectivo->iniciarCursor();
			while(estacionesColectivo->avanzarCursor()&&!recorridoDirectoEncontrado){
				Estacion* estacionIntermedia=estacionesColectivo->obtenerCursor();
				if(estacionIntermedia->verLinea()==estacionLlegada->verLinea()){
					Lista<Estacion*>  estacionesCercanasIntermedias;
					this->obtenerEstacionesCercanas(estacionIntermedia->verUbicacion(),
							&estacionesCercanasIntermedias);
					recorridoDirectoEncontrado=this->verRecorridoDirecto(estacionIntermedia->verUbicacion()
							,puntoPartida,
							&estacionesCercanasIntermedias,&estacionesPartida,&recorridoDirecto );
				}
			}

		}

	}
	if(recorridoDirecto.estaVacia()){
		std::cout<<"Todo maaaaaal"<<std::endl;
	}
	else{
		recorridoDirecto.iniciarCursor();
		while(recorridoDirecto.avanzarCursor()){
				Estacion *prueba=recorridoDirecto.obtenerCursor();
				std::cout<<prueba->verNombre()<<std::endl;;
		}
	}

}
bool Ciudad::verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada,
		Lista<Estacion*>*estacionesLlegada,Lista<Estacion*>*estacionesPartida,
		Lista<Estacion*>*recorridoDirecto ){


	obtenerEstacionesCercanas (puntoPartida,estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, estacionesLlegada);
	vincularPartidaLlegada(estacionesPartida, estacionesLlegada, recorridoDirecto);
	return !recorridoDirecto->estaVacia();


}



