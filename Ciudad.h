/*
 * Ciudad.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_CIUDAD_H_
#define SRC_CIUDAD_H_
#define DISTANCIA_MAX 500

#include "Estacion.h"
#include "Archivo.h"
#include  "util.h"
#include "Coordenadas.h"

class Ciudad {

	private:
		Lista<Estacion*>*estacionesTren;
		Lista<Estacion*>*bocasSubte;
		Lista<Estacion*>*estacionesColectivo;
		
		bool verRecorridoDirecto(Coordenadas puntoPartida, Coordenadas puntoLlegada,
				Lista<Estacion*>*estacionesLlegada,Lista<Estacion*>*estacionesPartida,
				Lista<Estacion*>*recorridoDirecto );

	public:
		/*post lee archivos metrobus, bocas subte, ferrocarriles para crear una lista
		 * de estaciones por tipo de transporte
		 * */	
		Ciudad();

		/*de prueba para ver la carga correcta de archivos*/
		Lista<Estacion*>*verEstacionesTren(){
			return this->estacionesTren;
		}
		Lista<Estacion*>* verBocasSubte(){
			return this->bocasSubte;
		}
		Lista<Estacion*>* verColectivos(){
			return this->estacionesColectivo;
		}
		void verRecorridoConCombinacion (Coordenadas puntoPartida, Coordenadas puntoLlegada);

		

		void verRecorridoDirecto (Coordenadas puntoPartida, Coordenadas puntoLlegada);

		void obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,Lista<Estacion*>*estacionesCercanas);

		void vincularPartidaLlegada(Lista<Estacion*> * estacionesPartida, Lista<Estacion*> * estacionesLlegada
				,Lista<Estacion*>*recorrido);
		~Ciudad();
};

#endif /* SRC_CIUDAD_H_ */
