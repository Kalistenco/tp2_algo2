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
	if(!recorridoDirecto.estaVacia()){
		this->leerRecorrido(&recorridoDirecto);

	}
	else{
		std::cout<<"No hay un camino directo entre los puntos dados, pruebe combinando..."<<std::endl;
	}
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
/*post:
 * imprime si existe un recorrido directo entre las coordenadas pedidas, si no existe busca e imprime un recorrido con combinacion*/

void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>  estacionesLlegada;
	Lista<Estacion*>recorridoCombinado;
	Lista<Estacion*>recorridoDirectoSupuesto;

	bool existeRecorridoDirecto=this->verRecorridoDirecto(puntoPartida, puntoLlegada,&recorridoDirectoSupuesto);
	if(existeRecorridoDirecto){
		recorridoCombinado.agregar(recorridoDirectoSupuesto);
	}
	else{
		obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
		bool recorridoCombinadoEncontrado=false;
		estacionesPartida.iniciarCursor();
		while(estacionesPartida.avanzarCursor()&&!recorridoCombinadoEncontrado){
			Estacion* estacionPartida=estacionesPartida.obtenerCursor();
			if(estacionPartida->verTipoTransporte()=="ferrocarril"){
				recorridoCombinadoEncontrado=this->buscarPuntoIntermedio(this->estacionesTren, estacionPartida,puntoLlegada,
							&recorridoCombinado);
				if(recorridoCombinadoEncontrado){
					recorridoCombinado.agregar(estacionPartida, 1);
				}
			}else if(estacionPartida->verTipoTransporte()=="subte"){
					recorridoCombinadoEncontrado=this->buscarPuntoIntermedio(this->bocasSubte, estacionPartida, puntoLlegada,
							&recorridoCombinado);
				if(recorridoCombinadoEncontrado){
					recorridoCombinado.agregar(estacionPartida, 1);
				}

			}else if(estacionPartida->verTipoTransporte()=="colectivo"){
					recorridoCombinadoEncontrado=this->buscarPuntoIntermedio(this->estacionesColectivo,estacionPartida, puntoLlegada,
							&recorridoCombinado);
				if(recorridoCombinadoEncontrado){
						recorridoCombinado.agregar(estacionPartida, 1);
				}
			}
		}
	}
	if(!recorridoCombinado.estaVacia()){
		this->leerRecorrido(&recorridoCombinado);

	}
	else{
		std::cout<<"No existe un recorrido con una combinacion..."<<std::endl;
	}
}

/*post: Imprime algunos campos de Lista<Estacion*> *recorrido
 * por ej: tipo de transporte|linea/ramal que corresponde|nombre de parada/estacion|coordenadas geograficas.*/
void Ciudad::leerRecorrido(Lista<Estacion*>*recorrido){
	recorrido->iniciarCursor();
	while(recorrido->avanzarCursor()){
		Estacion* estacion=recorrido->obtenerCursor();
		std::cout<<" | "<<estacion->verTipoTransporte()<< " | "<<estacion->verLinea()<<" | "<<" | "<<estacion->verNombre()
				<<" | "<<estacion->verUbicacionLatitud()<<" | "<<estacion->verUbicacionLongitud()<<" | "<<std::endl;
	}

}
/*post: devuelve true si encuentra un recorrido entre ambas coordenadas , es decir si hay 2 paradas/estaciones que estan en el mismo
 * tipo de transporte y linea o ramal.
 * */

bool Ciudad::verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada,

	Lista<Estacion*>*recorridoDirecto ){

	Lista<Estacion*>estacionesPartida;
	Lista<Estacion*>estacionesLlegada;
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada, &estacionesLlegada);

	vincularPartidaLlegada(&estacionesPartida, &estacionesLlegada, recorridoDirecto);
	return !(recorridoDirecto->estaVacia());


}

/*pre: lista de estaciones de un transporte , una parada/estacion de partida, lista recorridoCombinado vacia por referencia
 * post: devuelve true si encuentra un posible recorrido desde Estacion *estacionPartida hasta Coordenadas puntoLlegada
 *  pero combinando transporte y carga en Lista<Estacion*>*recorridoCombinado dichas estaciones */

bool Ciudad::buscarPuntoIntermedio(Lista<Estacion*>*estacionesARevisar, Estacion* estacionPartida, Coordenadas puntoLlegada,
		Lista<Estacion*>*recorridoCombinado){

	bool recorridoDirectoEncontrado=false;

	estacionesARevisar->iniciarCursor();
	while(estacionesARevisar->avanzarCursor()&&!recorridoDirectoEncontrado){
		Estacion* estacionIntermedia=estacionesARevisar->obtenerCursor();
		if(estacionIntermedia->verLinea()==estacionPartida->verLinea()){
			Lista<Estacion*> recorridoDirecto;
			Coordenadas ubicacionIntermedia=estacionIntermedia->verUbicacion();
			recorridoDirectoEncontrado=this->verRecorridoDirecto(ubicacionIntermedia, puntoLlegada, &recorridoDirecto);
			if(recorridoDirectoEncontrado){
				recorridoCombinado->agregar(recorridoDirecto);
				recorridoCombinado->agregar(estacionIntermedia, 1);
			}
		}
	}
		return recorridoDirectoEncontrado;
}



