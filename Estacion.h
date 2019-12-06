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
#include "Lista.h"
#include <vector>
class Estacion {
	private:
		std::string linea;
		std::string tipoTransporte; 
		std::string nombre;

		Lista<Estacion*>*adyacentes;
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
		void agregarAdyacente(Estacion * adyacente){
			/*si no es la misma estacion*/
			bool existe=false;

			if(*ubicacion!=adyacente->verUbicacion()){
				adyacentes->iniciarCursor();
				/*veo si esa adyacencia(la Estacion* adyacente) esta en la lista adyacentes*/
				while(adyacentes->avanzarCursor()&&!existe){
					existe=(adyacentes->obtenerCursor()->verNombre()==adyacente->verNombre());
				}
				/*si no está, la agrego*/
				if(!existe){
					this->adyacentes->agregar(adyacente);

				}
			}

		}
		unsigned int verCantAdyacentes(){
			return this->adyacentes->contarElementos();
		}
		void obtenerAdyacente(std::vector<Estacion> *adyacentesVacia){
			if(!adyacentes->estaVacia()){
				adyacentes->iniciarCursor();
				while(adyacentes->avanzarCursor()){
					//adyacentesVacia->push_back(*(adyacentes.obtenerCursor()));
				}
			}
		}
		Lista<Estacion*>*obtenerAdyacentes(){
			return this->adyacentes;
		}

		bool operator !=(Estacion* aComparar){
			return (aComparar->verUbicacion()!=(*ubicacion))&&(this->nombre!=aComparar->nombre);
		}
		std::string verLinea(){
			return this->linea;
		}

		std::string verNombre(){
			return this->nombre;
		}

		~Estacion(){
			delete this->ubicacion;

			delete adyacentes;
	}
};

#endif /* SRC_ESTACION_H_ */
