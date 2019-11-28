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
/*
	Archivo colectivos(ARCHIVO_COLECTIVOS);
	Lista<std::string> registrosEstacionesColectivo;
	colectivos.leerArchivo(registrosEstacionesColectivo);
*/
	Archivo subtes(ARCHIVO_SUBTES);
	Lista<std::string> registrosBocasSubte;
	subtes.leerArchivo(registrosBocasSubte);

	/*Recorrido y carga de registros en listas*/

	//cargarDatos(this->estacionesColectivo, registrosEstacionesColectivo, "colectivo");
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
	
	cargarEstacionesCercanas(this->bocasSubte, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesColectivo, estacionesCercanas, ubicacionUsuario);
	cargarEstacionesCercanas(this->estacionesTren, estacionesCercanas, ubicacionUsuario);
}

void Ciudad::cargarEstacionesCercanas(Lista<Estacion*>* medioDeTransporte, Lista<Estacion*>* datosCargados, Coordenadas ubicacion) {

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

void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>  estacionesPartida;
	Lista<Estacion*>	recorridoCombinado;
	Lista<Estacion*>	recorridoDirectoSupuesto;

	Lista<Estacion*>*recorridoMinimo=NULL;

	bool existeRecorridoDirecto=false;//this->verRecorridoDirecto(puntoPartida, puntoLlegada,&recorridoDirectoSupuesto);
	if(existeRecorridoDirecto){
		recorridoCombinado.agregar(recorridoDirectoSupuesto);
	}
	else{
		obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
		bool recorridoCombinadoEncontrado=false;
		estacionesPartida.iniciarCursor();
		while(estacionesPartida.avanzarCursor()&&!recorridoCombinadoEncontrado){
			Estacion* estacionPartida=estacionesPartida.obtenerCursor();
			Lista<Estacion*>recorridoIntermedio;
			if(estacionPartida->verTipoTransporte()=="ferrocarril"){
				recorridoCombinadoEncontrado=buscarPuntoIntermedio(this->estacionesTren, estacionPartida,puntoLlegada,&recorridoIntermedio);

			}else if(estacionPartida->verTipoTransporte()=="subte"){
				recorridoCombinadoEncontrado=buscarPuntoIntermedio(this->bocasSubte, estacionPartida, puntoLlegada,&recorridoIntermedio);

			}else if(estacionPartida->verTipoTransporte()=="colectivo"){
				recorridoCombinadoEncontrado=buscarPuntoIntermedio(this->estacionesColectivo,estacionPartida, puntoLlegada,
							&recorridoIntermedio);
			}
			if(recorridoCombinadoEncontrado){
				recorridoCombinado.agregar(recorridoIntermedio);
				recorridoCombinado.agregar(estacionPartida,1);
				std::cout<<"tiene tantos elementos el recorridoCombinado "<<recorridoCombinado.contarElementos()<<std::endl;
				this->leerRecorrido(&recorridoCombinado);
			}/*
			if(recorridoMinimo!=NULL){
				//calcular si es minima distancia y guardar nuevo recorrido en recorridoMinimo
			}else{
				recorridoMinimo=&recorridoCombinado;
			}*/
			//recorridoCombinadoEncontrado=!(recorridoIntermedio.estaVacia());
		}
	}
	/*
	if(!recorridoMinimo->estaVacia()){
		this->leerRecorrido(recorridoMinimo);
	}
	else{
		std::cout<<"No existe un recorrido con una combinacion..."<<std::endl;
	}*/
}
bool Ciudad::esMinimo(Lista<Estacion*>*minimo, Lista<Estacion*>&aEvaluar){
	minimo->iniciarCursor();
	while(minimo->avanzarCursor()){
		minimo->obtenerCursor()->verUbicacion();
	}

	Coordenadas origen=minimo->obtener(1)->verUbicacion();
	Coordenadas intermedio=minimo->obtener(2)->verUbicacion();
	Coordenadas destino=minimo->obtener(3)->verUbicacion();
	unsigned int distancia=origen.distanciaMetros(intermedio)+intermedio.distanciaMetros(destino);

	Coordenadas origenEvaluado=aEvaluar.obtener(1)->verUbicacion();
	Coordenadas intermedioEvaluado=aEvaluar.obtener(2)->verUbicacion();
	Coordenadas destinoEvaluado=aEvaluar.obtener(3)->verUbicacion();
	unsigned int distanciaEvaluada=origenEvaluado.distanciaMetros(intermedio)+intermedioEvaluado.distanciaMetros(destinoEvaluado);
return distancia<distanciaEvaluada;
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
	Estacion* estacionIntermedia;
	estacionesARevisar->iniciarCursor();
	while(estacionesARevisar->avanzarCursor()&&!recorridoDirectoEncontrado){
		estacionIntermedia=estacionesARevisar->obtenerCursor();
		if(estacionIntermedia->verLinea()==estacionPartida->verLinea()&&estacionIntermedia!=estacionPartida){
			Lista<Estacion*> recorridoDirecto;
			Coordenadas ubicacionIntermedia=estacionIntermedia->verUbicacion();
			recorridoDirectoEncontrado=verRecorridoDirecto(ubicacionIntermedia, puntoLlegada, &recorridoDirecto);
			if(recorridoDirectoEncontrado){
				recorridoCombinado->agregar(recorridoDirecto);
				recorridoCombinado->agregar(estacionIntermedia, 1);
			}
		}
	}
		return recorridoDirectoEncontrado;
}




