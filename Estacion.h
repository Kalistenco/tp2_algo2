/*
 * Estacion.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_ESTACION_H_
#define SRC_ESTACION_H_

#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Coordenadas.h"

class Estacion {
	private:
		std::string linea;
		std::string tipoTransporte; 
		std::string nombre;

		Coordenadas * ubicacion;

		void leerInformacionSubte(std::string informacion);
		void leerInformacionFerrocarril(std::string informacion);
		void leerInformacionColectivo(std::string informacion);

	public:

		Estacion(std::string informacionEstacion, std::string tipoTransporte);

		Coordenadas verUbicacion(){
			return (*ubicacion);
		}
		std::string verTipoTransporte(){
			return this->tipoTransporte;
		}
        	float verUbicacionLatitud(){
        	return this->ubicacion->verLatitud();
        }
		
		float verUbicacionLongitud(){
        	return this->ubicacion->verLongitud();
        }

		std::string verLinea(){
			return this->linea;
		}

		std::string verNombre(){
			return this->nombre;
		}

		~Estacion(){
			delete this->ubicacion;
	}
};

#endif /* SRC_ESTACION_H_ */
