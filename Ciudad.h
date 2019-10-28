/*
 * Ciudad.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_CIUDAD_H_
#define SRC_CIUDAD_H_
#define DISTANCIA_MAX 500

#include "Tren.h"
#include "Colectivo.h"
#include "Subte.h"
#include "Archivo.h"
#include  "util.h"

class Ciudad {

	private:
		Lista<Tren*>*estacionesTren;
		Lista<Subte*>*bocasSubte;
		Lista<Colectivo*>*estacionesColectivo;
		bool estanEnElMismoRamal(Tren* origen, Tren* destino);

	public:
		/*post lee archivos metrobus, bocas subte, ferrocarriles para crear una lista
		 * de estaciones por tipo de transporte
		 * */	
		Ciudad();
	
		Lista<Tren*> recorridoDirectoTren();
		/* agregar opciones de pedido de coordenadas */
		Coordenadas pedirOrigen();
		Coordenadas pedirDestino();
		/*de prueba para ver la carga correcta de archivos*/
		Lista<Tren*>*verEstacionesTren(){
			return this->estacionesTren;
		}
		Lista<Subte*>* verBocasSubte(){
			return this->bocasSubte;
		}
		Lista<Colectivo*>* verColectivos(){
			return this->estacionesColectivo;
		}

		~Ciudad();
};

#endif /* SRC_CIUDAD_H_ */
