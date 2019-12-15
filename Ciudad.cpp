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
#include "Recorrido.h"
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


	cargarDatos(this->bocasSubte, registrosBocasSubte, "subte");
	std::cout<<"cargaron datos de subtes"<<std::endl;

	cargarDatos(this->estacionesTren, registrosEstacionesTren, "ferrocarril");
	std::cout<<"cargaron datos de trenes"<<std::endl;
	cargarDatos(this->estacionesColectivo, registrosEstacionesColectivo, "colectivo");
	std::cout<<"cargaron datos de colectivos"<<std::endl;

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
		if(distancia < 1000&&distancia>0) {
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
		this->cargarAdyacentesPorMedioTransporte(&trenes, iterando);
		this->cargarAdyacentesPorMedioTransporte(&subte, iterando);
		this->cargarAdyacentesPorMedioTransporte(&paradasColectivoAux, iterando);
	}
std::cout<<"cargaron adyacencias "<<std::endl;
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

		if(ubicacionEstacion.distanciaMetros(ubicacion) < 1000) {
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
	/*recorridoMinimo deberia llegar por referencia*/
	Recorrido recorridoMinimo;
	bool hayRecorrido=false;
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
				/*RECORRIDO recorridoMinimo
				 * en principio estaria vacio*/
				estacionesAdyacentes->iniciarCursor();
				while(estacionesAdyacentes->avanzarCursor()&&!existeCombinacion){
					Estacion* adyacente=estacionesAdyacentes->obtenerCursor();
					existeCombinacion=hayCombinacion(adyacente,llegada,recorridoIntermedio,estacionesLlegada );
					if(existeCombinacion){
						/*si se encontro combinacion entonces se tiene un objeto Recorrido recorridoIntermedio
						 * con una estacion intermedia y destino de minima distancia*/
						recorridoIntermedio->agregar(estacionIntermedia,1);
						/*luego de agregar la otra estacion intermedia en la primera posicion de Recorrido
						 * recorridoIntermedio y calculo nuevamente la distancia

						evaluo el recorrido anterior con RecorridoMinimo de tda ciudad
						 * si este esta vacio (la primer iteracion siempre lo va a tomar como vacio)
						 * entonces recorridoMinimo va a pasar a ser recorridoIntemedio*/
					}
				}
				/*al tener Recorrido recorridoMinimo quito la condicion existeCombinacion del 'while'
				 * entonces prueba con otra estacion adyacente y hace el mismo proceso*/
			}
		}
	}
}
void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>estacionesPartida;
	Lista<Estacion*>estacionesLlegada;
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada,&estacionesLlegada );
	Recorrido recorridoMinimo;

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
			/* se supone que para esta parte ya se tiene un Recorrido recorridoMinimo que sale de buscarEstacionIntermdia()
			 * y que a su vez sale de hayCombinacion()*/
			recorridoCombinado.agregar(estacionPartida,1);
			/*tengo que tener un recorridoMinimo vacio y cargarle el que tengo hasta ahora si es que esta vacio
			 * si no lo compara con el que tenga guardado.
			 * Este ultimo puede ser un recorridoMinimo de tda ciudad*/

			this->leerRecorrido(&recorridoCombinado);
		}
		else{
			std::cout<<"No Hay recorrido combinado "<<std::endl;
		}

	}

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
/*


bool Ciudad::hayCombinacion(Estacion *intermedia, Coordenadas llegada,
		 Lista<Estacion*>*estacionesLlegada, Recorrido *intermedio){
	bool hayRecorrido=false;
	estacionesLlegada->iniciarCursor();
	while(estacionesLlegada->avanzarCursor()&&!hayRecorrido){
		Estacion* destino=estacionesLlegada->obtenerCursor();
		hayRecorrido=destino->verLinea()==intermedia->verLinea();
		if(hayRecorrido){
			if(intermedio->estaVacio()){
				intermedio->agregarAlFinal(destino);
				intermedio->agregarAlPrincipio(intermedia);
			}else{
				Recorrido alternativo;
				alternativo.agregarAlFinal(destino);
				alternativo.agregarAlPrincipio(intermedia);
				bool esMasCorto=*intermedio<&alternativo;
				if(esMasCorto){
					*intermedio=alternativo;
				}

			}
			hayRecorrido=false;
		}

	}
	return !intermedio->estaVacio();
}*/
/*
void Ciudad::buscarEstacionIntermedia(Lista<Estacion*>*estaciones, Estacion*partida,
		Coordenadas llegada, Lista<Estacion*>*estacionesLlegada,
		Recorrido *recorridoIntermedioAnterior){
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
					Recorrido intermedio;
					existeCombinacion=hayCombinacion(adyacente,llegada,
							estacionesLlegada, &intermedio );
					if(existeCombinacion){
					
						intermedio.agregarAlPrincipio(estacionIntermedia);
						if(recorridoIntermedioAnterior->estaVacio()){
							*recorridoIntermedioAnterior=intermedio;
						}
						else{
							bool esMasCorto=(*recorridoIntermedioAnterior)<&intermedio;
							if(esMasCorto){
								*recorridoIntermedioAnterior=intermedio;
							}
						}
						existeCombinacion=false;
						
					}
				}
				
			}
		}
	}
}
*/
/*
void Ciudad::verRecorridoConCombinacion(Coordenadas puntoPartida, Coordenadas puntoLlegada){
	Lista<Estacion*>estacionesPartida;
	Lista<Estacion*>estacionesLlegada;
	obtenerEstacionesCercanas (puntoPartida,&estacionesPartida );
	obtenerEstacionesCercanas (puntoLlegada,&estacionesLlegada );
	Recorrido recorridoCombinadoMinimo;
	bool recorridoCombinadoEncontrado=false;
	estacionesPartida.iniciarCursor();
	while(estacionesPartida.avanzarCursor()&&!recorridoCombinadoEncontrado){
		Recorrido recorridoCombinadoAlternativo;
		Estacion* estacionPartida=estacionesPartida.obtenerCursor();
		if(estacionPartida->verTipoTransporte()=="ferrocarril"){

			buscarEstacionIntermedia(estacionesTren,estacionPartida, puntoLlegada,
								&estacionesLlegada, &recorridoCombinadoAlternativo );
		}else if(estacionPartida->verTipoTransporte()=="subte"){

			buscarEstacionIntermedia(bocasSubte,estacionPartida, puntoLlegada,
							&estacionesLlegada, &recorridoCombinadoAlternativo);
		}else if(estacionPartida->verTipoTransporte()=="colectivo"){

			buscarEstacionIntermedia(estacionesColectivo,estacionPartida, puntoLlegada,
							&estacionesLlegada, &recorridoCombinadoAlternativo);
		}
		recorridoCombinadoEncontrado=!recorridoCombinadoAlternativo.estaVacio();
		if(recorridoCombinadoEncontrado){
			
			recorridoCombinadoAlternativo.agregarAlPrincipio(estacionPartida);

			if(recorridoCombinadoMinimo.estaVacio()){
				recorridoCombinadoMinimo=recorridoCombinadoAlternativo;
			}
			else{
				bool mejorDistancia=recorridoCombinadoAlternativo<&recorridoCombinadoMinimo;
				if(mejorDistancia){
					recorridoCombinadoMinimo=recorridoCombinadoAlternativo;
				}
			}
		if(!recorridoCombinadoMinimo.estaVacio()){
			recorridoCombinadoMinimo.leerRecorrido();
		}
		}
		else{
			std::cout<<"No Hay recorrido combinado "<<std::endl;
		}
	}

}
*/


