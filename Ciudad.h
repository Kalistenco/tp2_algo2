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
class Ciudad {
private:
	typedef unsigned int ui;
	Lista<Estacion*>*estacionesTren;
	Lista<Estacion*>*bocasSubte;
	Lista<Estacion*>*estacionesMetrobus;


private:

public:
	/*post lee archivos metrobus, bocas subte, ferrocarriles para crear una lista
	 * de estaciones por tipo de transporte
	 * */
	Ciudad();
	/*de prueba para ver la carga correcta de archivos*/
	Lista<Estacion*>*verEstacionesTren(){
		return this->estacionesTren;
	}


	~Ciudad();
};

#endif /* SRC_CIUDAD_H_ */
