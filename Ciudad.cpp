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

	cargarDatos(this->estacionesColectivo, registrosEstacionesColectivo, "colectivo");
	cargarDatos(this->bocasSubte, registrosBocasSubte, "subte");
	cargarDatos(this->estacionesTren, registrosEstacionesTren, "ferrocarril");
}

void Ciudad::cargarDatos(Lista<Estacion*>* medioDeTransporte, Lista<std::string> datos, std::string tipoDeTransporte){
	
	datos.iniciarCursor();

	while(datos.avanzarCursor()) {
		std::string infoEstacion = datos.obtenerCursor();
		Estacion* nuevaEstacion = new Estacion (infoEstacion, tipoDeTransporte);
		medioDeTransporte->agregar(nuevaEstacion);
	}
}

Ciudad::~Ciudad(){

	borrarDatos(this->bocasSubte);
	borrarDatos(this->estacionesColectivo);
	borrarDatos(this->estacionesTren);
}

void Ciudad::borrarDatos(Lista<Estacion*>* medioDeTransporte){

	medioDeTransporte->iniciarCursor();

	while (medioDeTransporte->avanzarCursor()){
		delete medioDeTransporte->obtenerCursor();
	}

	delete medioDeTransporte;
}

void Ciudad::verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>  estacionesLlegada;
	Lista<Estacion*> recorridoDirecto;

	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, &estacionesLlegada);
	vincularPartidaLlegada(&estacionesPartida, &estacionesLlegada, &recorridoDirecto);
}


void Ciudad::obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,
	Lista<Estacion*>*estacionesCercanas){
	
	cargarEstacionesCercanas(this->bocasSubte, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesColectivo, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesTren, estacionesCercanas, ubicacionUsuario);
}

void Ciudad::cargarEstacionesCercanas(Lista<Estacion*>* medioDeTransporte, Lista<Estacion*>* datosCargados, Coordenadas ubicacion) {

	medioDeTransporte->iniciarCursor();

	while(medioDeTransporte->avanzarCursor()){
		Coordenadas ubicacionEstacion = medioDeTransporte->obtenerCursor()->verUbicacion();

		if(ubicacionEstacion.distanciaMetros(ubicacion) < 250) {
			Estacion * trenIterado = medioDeTransporte->obtenerCursor();
			datosCargados->agregar(trenIterado);
		}
	}
}

void Ciudad::vincularPartidaLlegada(Lista<Estacion*> * estacionesPartida, Lista<Estacion*> * estacionesLlegada,
	Lista<Estacion*>*recorridoDirecto){

	bool recorridoEncontrado = false;

	estacionesPartida->iniciarCursor();

	while(estacionesPartida->avanzarCursor() && recorridoEncontrado == false){

		Estacion *estacionIterada=estacionesPartida->obtenerCursor();
		estacionesLlegada->iniciarCursor();

		while(estacionesLlegada->avanzarCursor()){

			Estacion* estacionLlegada=estacionesLlegada->obtenerCursor();

			if(estacionIterada->verLinea() == estacionLlegada->verLinea() && recorridoEncontrado == false){

				recorridoDirecto->agregar(estacionesPartida->obtenerCursor());
				recorridoDirecto->agregar(estacionesLlegada->obtenerCursor());
				recorridoEncontrado = true;
			}
		}
	}
}

void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>  estacionesLlegada;
	Lista<Estacion*>recorridoCombinado;
	//Lista<Lista<Estacion*>> recorridosCombinados;
	/*carga estaciones cercanas a los puntos dados por el usuario*/
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, &estacionesLlegada);
	bool recorridoDirectoEncontrado=false;

	estacionesLlegada.iniciarCursor();
	while(estacionesLlegada.avanzarCursor()&&!recorridoDirectoEncontrado){
		Estacion* estacionLlegada=estacionesLlegada.obtenerCursor();
		Coordenadas ubicacionEstacionIntermedia=estacionLlegada->verUbicacion();

		/*para un tipo de estacion(tipo de transporte) de llegada busca las que sean de ese transporte y de la misma linea
		 -ramal-etc. Para cada estacion con esas condiciones busca las estaciones cercanas y junto a las estaciones cercanas
		 a las de partida usa el mismo algoritmo del recorrido directo. Si lo encuentra corta el ciclo e imprime.*/

		if(estacionLlegada->verTipoTransporte()=="ferrocarril"){

			recorridoDirectoEncontrado=	this->buscarPuntoIntermedio(this->estacionesTren, estacionLlegada,puntoPartida,
					&recorridoCombinado, &estacionesPartida);

		}
		else if(estacionLlegada->verTipoTransporte()=="subte"){
			recorridoDirectoEncontrado=this->buscarPuntoIntermedio(this->bocasSubte, estacionLlegada, puntoPartida,
					&recorridoCombinado,  &estacionesPartida);


		}else if(estacionLlegada->verTipoTransporte()=="colectivo"){
			recorridoDirectoEncontrado=this->buscarPuntoIntermedio(this->estacionesColectivo,estacionLlegada, puntoPartida,
					&recorridoCombinado,  &estacionesPartida );
		}

	}


}

bool Ciudad::verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada,
	Lista<Estacion*>*estacionesLlegada,Lista<Estacion*>*estacionesPartida,
	Lista<Estacion*>*recorridoDirecto ){

	obtenerEstacionesCercanas (puntoPartida,estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, estacionesLlegada);
	vincularPartidaLlegada(estacionesPartida, estacionesLlegada, recorridoDirecto);
	return !(recorridoDirecto->estaVacia());


}

bool Ciudad::buscarPuntoIntermedio(Lista<Estacion*>*estaciones, Estacion* llegada, Coordenadas puntoPartida,
		Lista<Estacion*>*recorridoCombinado,  Lista<Estacion*>*partida){
		bool recorridoDirectoEncontrado=false;

		estaciones->iniciarCursor();
		while(estaciones->avanzarCursor()&&!recorridoDirectoEncontrado){
			Estacion* estacionIntermedia=estaciones->obtenerCursor();
			if(estacionIntermedia->verLinea()==llegada->verLinea()){
				Lista<Estacion*>  estacionesCercanasIntermedias;
				Lista<Estacion*> recorridoDirecto;

				Coordenadas ubicacionIntermedia=estacionIntermedia->verUbicacion();
				/*busco estaciones cercanas a la posible estacion intermedia del recorrido*/
				this->obtenerEstacionesCercanas(ubicacionIntermedia, &estacionesCercanasIntermedias);
				/*Con las estaciones cercanas al punto intermedio busco si alguna esta en el tipo de trasnporte
				 * y linea que las estaciones de partida.
				 * Es decir busco un recorrido directo entr esas 2 listas de estaciones*/
				recorridoDirectoEncontrado=this->verRecorridoDirecto(ubicacionIntermedia
						,puntoPartida,
						&estacionesCercanasIntermedias,partida,&recorridoDirecto );
				/*si resulta que la estacion intermedia es la misma que la de llegada, entonces solo
				 * se agrega una vez al recorrido*/
				if(recorridoDirectoEncontrado){
					recorridoCombinado->agregar(recorridoDirecto);
					if((llegada->verUbicacionLatitud()!=estacionIntermedia->verUbicacionLatitud())
							&&llegada->verUbicacionLongitud()!=estacionIntermedia->verUbicacionLongitud()){
						recorridoCombinado->agregar(estacionIntermedia);
						recorridoCombinado->agregar(llegada);
					}
					else{
						recorridoCombinado->agregar(llegada);
					}
				}
			}
		}
		return recorridoDirectoEncontrado;

}



