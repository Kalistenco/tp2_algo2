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
	//this->paradasColectivoAux.agregar(*estacionesColectivo);
	this->cargarAdyacentes();
}
void Ciudad::cargarAdyacentesPorMedioTransporte(Lista<Estacion*>*medioTransporte,
		Estacion* estacionAbuscarAdyacencia){

	Coordenadas ubicacion=estacionAbuscarAdyacencia->verUbicacion();
	unsigned int distancia=0;
	medioTransporte->iniciarCursor();
	while(medioTransporte->avanzarCursor()){
		Estacion* posibleAdyacencia=medioTransporte->obtenerCursor();
		distancia =ubicacion.distanciaMetros(posibleAdyacencia->verUbicacion());
		/*si es la misma estacion la distancia a si misma debe ser 0 y no la considero*/
		if(distancia < 250&&distancia>0) {
			/*si es una boca distinta pero de la misma estacion no la considero*/
			if(estacionAbuscarAdyacencia->verNombre()!=medioTransporte->
					obtenerCursor()->verNombre()){
				//std::cout<<estacionAbuscarAdyacencia->verNombre()<<medioTransporte->obtenerCursor()->verNombre()<<std::endl;
				estacionAbuscarAdyacencia->agregarAdyacente(medioTransporte->obtenerCursor());
			}
		}
	}


}
/*carga a cada Estacion sus estaciones cercanas de cualquier tipo*/
void Ciudad::cargarAdyacentes(){
	//coste de O(n2)
	//auxiliar
	Lista<Estacion*>subte;
	subte.agregar(*bocasSubte);
	Lista<Estacion*>trenes;
	trenes.agregar(*estacionesTren);
	//Lista<Estacion*>colectivos;

	this->estacionesTren->iniciarCursor();
	while(estacionesTren->avanzarCursor()){

		Estacion* iterando=estacionesTren->obtenerCursor();
		//Coordenadas ubicacion=iterando->verUbicacion();
		this->cargarAdyacentesPorMedioTransporte(&subte, iterando);
		this->cargarAdyacentesPorMedioTransporte(&trenes, iterando);
		this->cargarAdyacentesPorMedioTransporte(this->estacionesColectivo, iterando);
	}

	this->bocasSubte->iniciarCursor();
	while(bocasSubte->avanzarCursor()){

		Estacion* iterando=bocasSubte->obtenerCursor();
		//Coordenadas ubicacion=iterando->verUbicacion();
		this->cargarAdyacentesPorMedioTransporte(&trenes, iterando);
		this->cargarAdyacentesPorMedioTransporte(this->estacionesColectivo, iterando);
		this->cargarAdyacentesPorMedioTransporte(&subte, iterando);
	}

	this->estacionesColectivo->iniciarCursor();
	while(estacionesColectivo->avanzarCursor()){

		Estacion* iterando=estacionesColectivo->obtenerCursor();
		Coordenadas ubicacion=iterando->verUbicacion();
		this->cargarAdyacentesPorMedioTransporte(&trenes, iterando);
		this->cargarAdyacentesPorMedioTransporte(&subte, iterando);
		//this->cargarAdyacentesPorMedioTransporte(&paradasColectivoAux, iterando);
	}

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
/*pre: coordenadas geograficas no vacias y de caba
 * post: busca e imprime un posible camino entre esos puntos cuando solamente los une un medio de transporte
 * */
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

/*pre: Coordenadas geograficas de caba y Lista<Estacion*>* estacionesCercanas vacia.*/
/*post: agrega en estacionesCercanas las estaciones/paradas con un rango de 250m a la ubicacionUsuario
 * como pueden ser bocas de subte, paradas de colectivo, estaciones de tren.. */

void Ciudad::obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,
	Lista<Estacion*>*estacionesCercanas){

	cargarEstacionesCercanas(bocasSubte, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesColectivo, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesTren, estacionesCercanas, ubicacionUsuario);
}


void Ciudad::cargarEstacionesCercanas(Lista<Estacion*>* medioDeTransporte
		,Lista<Estacion*>* datosCargados, Coordenadas ubicacion) {

	medioDeTransporte->iniciarCursor();

	while(medioDeTransporte->avanzarCursor()){
		Coordenadas ubicacionEstacion = medioDeTransporte->obtenerCursor()->verUbicacion();

		if(ubicacionEstacion.distanciaMetros(ubicacion) < 250) {
			Estacion * estacion = medioDeTransporte->obtenerCursor();
			datosCargados->agregar(estacion);
		}
	}

}

/*pre: Lista<Estacion*>* estacionesPartida y estacionesLlegada no vacias y Lista<Estacion*>* recorridoDirecto vacia*/
/*post:carga en recorridoDirecto las estaciones/paradas que tiene en comun linea/ramal dependiendo tipo de transporte*/
void Ciudad::vincularPartidaLlegada(Lista<Estacion*> * estacionesPartida, Lista<Estacion*> * estacionesLlegada,
	Lista<Estacion*>*recorridoDirecto){

	bool recorridoEncontrado = false;

	estacionesPartida->iniciarCursor();

	while(estacionesPartida->avanzarCursor() && !recorridoEncontrado){

		Estacion *estacionIterada=estacionesPartida->obtenerCursor();
		estacionesLlegada->iniciarCursor();

		while(estacionesLlegada->avanzarCursor()){

			Estacion* estacionLlegada=estacionesLlegada->obtenerCursor();

			if(estacionIterada->verLinea() == estacionLlegada->verLinea() && !recorridoEncontrado){

				recorridoDirecto->agregar(estacionesPartida->obtenerCursor());
				recorridoDirecto->agregar(estacionesLlegada->obtenerCursor());
				recorridoEncontrado = true;
			}
		}
	}
}
/*pre: Coordenadas geograficas de caba
 * post:imprime si existe un recorrido directo entre las coordenadas pedidas,
 *  si no existe busca e imprime un recorrido con combinacion*/
bool Ciudad::hayCombinacion(Estacion *intermedia, Coordenadas llegada,
		Lista<Estacion*>*recorridoIntermedio, Lista<Estacion*>*estacionesLlegada){

	//Lista<Estacion*>estacionesLlegada;
	bool hayRecorrido=false;
	//this->obtenerEstacionesCercanas(llegada,&estacionesLlegada);
	estacionesLlegada->iniciarCursor();
	while(estacionesLlegada->avanzarCursor()&&!hayRecorrido){
		Estacion* destino=estacionesLlegada->obtenerCursor();
		hayRecorrido=destino->verLinea()==intermedia->verLinea();
		if(hayRecorrido){
			recorridoIntermedio->agregar(destino);
			recorridoIntermedio->agregar(intermedia,1);
		}
	}
	return hayRecorrido;
}

void Ciudad::buscarEstacionIntermedia(Lista<Estacion*>*estaciones, Estacion*partida,
		Coordenadas llegada,Lista<Estacion*>*recorridoIntermedio, Lista<Estacion*>*estacionesLlegada){
	bool existeCombinacion=false;
	estaciones->iniciarCursor();
	while(estaciones->avanzarCursor()){
		Estacion *estacionIntermedia=estaciones->obtenerCursor();
		if(partida->verLinea()==estacionIntermedia->verLinea()&&partida!=estacionIntermedia){

			Lista<Estacion*>*estacionesAdyacentes=estacionIntermedia->obtenerAdyacentes();
			if(!estacionesAdyacentes->estaVacia()){

				estacionesAdyacentes->iniciarCursor();
				while(estacionesAdyacentes->avanzarCursor()&&!existeCombinacion){
					Estacion* adyacente=estacionesAdyacentes->obtenerCursor();

					existeCombinacion=hayCombinacion(adyacente,llegada,recorridoIntermedio,estacionesLlegada );
					if(existeCombinacion){
						recorridoIntermedio->agregar(estacionIntermedia,1);
					}
				}
			}
		}
	}
}
void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>estacionesPartida;
	Lista<Estacion*>estacionesLlegada;
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada,&estacionesLlegada );

	bool recorridoCombinadoEncontrado=false;
	estacionesPartida.iniciarCursor();
	while(estacionesPartida.avanzarCursor()&&!recorridoCombinadoEncontrado){
		Lista<Estacion*>recorridoCombinado;
		Estacion* estacionPartida=estacionesPartida.obtenerCursor();
		if(estacionPartida->verTipoTransporte()=="ferrocarril"){
			buscarEstacionIntermedia(estacionesTren,estacionPartida, puntoLlegada, &recorridoCombinado,&estacionesLlegada );
		}else if(estacionPartida->verTipoTransporte()=="subte"){
			buscarEstacionIntermedia(bocasSubte,estacionPartida, puntoLlegada, &recorridoCombinado,
				&estacionesLlegada);
		}else if(estacionPartida->verTipoTransporte()=="colectivo"){
		buscarEstacionIntermedia(estacionesColectivo,estacionPartida, puntoLlegada, &recorridoCombinado, &estacionesLlegada);
		}
		recorridoCombinadoEncontrado=!recorridoCombinado.estaVacia();
		if(!recorridoCombinado.estaVacia()){
			recorridoCombinado.agregar(estacionPartida,1);
			this->leerRecorrido(&recorridoCombinado);
		}
		else{
			std::cout<<"No Hay recorrido combinado "<<std::endl;
		}
			/*if(!recorridoMinimo.estaVacia()){
				//si ya hay un recorridoMinimo calculo y compara distancias
				unsigned int distancia=this->verDistancia(&recorridoCombinado);
				if(distancia<distanciaMinima){
					//guardar en recorridoMinimo los elementos de recorridoCombinado borrando los de
					//recorridoMinimo anterior ¿se borran las referencias guardadas? probar y pasar a copia
					//de estaciones en ese caso;
					recorridoMinimo=recorridoCombinado;
					distanciaMinima=distancia;
				}
			}else{
				//si recorridoMinimo esta vacia
				recorridoMinimo.agregar(recorridoCombinado);
				distanciaMinima=this->verDistancia(&recorridoMinimo);
			}*/
		}
	//}
/*
	if(!recorridoMinimo.estaVacia()){
		this->leerRecorrido(&recorridoMinimo);
	}
	else{
		std::cout<<"No existe un recorrido con una combinacion..."<<std::endl;
	}*/
}

unsigned int Ciudad::verDistancia(Lista<Estacion*>*recorrido){
	unsigned int distancia=0;
	std::vector<Coordenadas> posicionesEstaciones;
	recorrido->iniciarCursor();
	while(recorrido->avanzarCursor()){
		Coordenadas posicionEstacion=recorrido->obtenerCursor()->verUbicacion();
		posicionesEstaciones.push_back(posicionEstacion);
	}
	for(unsigned int i=0; i<posicionesEstaciones.size();i++){
		if((i+1)<=posicionesEstaciones.size()){
			distancia+=posicionesEstaciones[i].distanciaMetros(posicionesEstaciones[i+1]);
		}
	}
	return distancia;
}
/*post: Imprime algunos campos de Lista<Estacion*> *recorrido
 * por ej: tipo de transporte|linea/ramal que corresponde|nombre de parada/estacion|coordenadas geograficas.*/
void Ciudad::leerRecorrido(Lista<Estacion*>*recorrido){
	recorrido->iniciarCursor();
	while(recorrido->avanzarCursor()){
		Estacion* estacion=recorrido->obtenerCursor();
		std::cout<<" | "<<estacion->verTipoTransporte()<< " | "
				<<estacion->verLinea()<<" | "<<" | "<<estacion->verNombre()
				<<" | "<<estacion->verUbicacionLatitud()<<" | "<<estacion->verUbicacionLongitud()<<" | "<<std::endl;
	}

}


