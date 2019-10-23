/*
 * Estacion.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include "Estacion.h"

Estacion::Estacion(std::string informacionEstacion, std::string tipoTransporte){
	if(tipoTransporte=="ferrocarril"){
		this->leerInformacionFerrocarril(informacionEstacion);
	}
	else if(tipoTransporte=="subte"){
		this->leerInformacionSubte(informacionEstacion);
	}
	else if(tipoTransporte=="colectivo"){
		this->leerInformacionColectivo(informacionEstacion);
	}
}

void Estacion::leerInformacionSubte(std::string informacion){
	std::stringstream registro;
	std::string dato;
	std::string longitud, latitud;
	registro<<informacion;
	unsigned int columnaLeida=1;

	while(getline(registro,dato,',')){
				switch(columnaLeida){
				case 1:{
					longitud=dato;
				}break;

				case 2:{
					latitud=dato;
				}break;

				case 4:{
					this->linea=dato;
				}break;
			}
				columnaLeida+=1;
		}

	this->ubicacion = new Coordenadas (longitud, latitud);
}

void Estacion::leerInformacionFerrocarril(std::string informacion){
	std::stringstream registro;
	std::string dato;
	std::string longitud, latitud;
	registro<<informacion;
	unsigned int columnaLeida=1;

	while(getline(registro,dato,',')){
		switch(columnaLeida){
			case 1:{
				longitud=dato;
			}break;

			case 2:{
				latitud=dato;
			}break;

			case 5:{
				this->linea=dato;
			}break;
		}
		columnaLeida+=1;
	}

	this->ubicacion = new Coordenadas (longitud, latitud);
}

void Estacion::leerInformacionColectivo(std::string informacion){
	std::stringstream registro;
	std::string dato;
	std::string longitud, latitud;
	registro<<informacion;
	unsigned int columnaLeida=1;

	while(getline(registro,dato,',')){
			switch(columnaLeida){
			case 4:{
				longitud=dato;
			}break;

			case 5:{
				latitud=dato;
			}break;

			case 8:{
				this->linea=dato;
			}break;
		}
			columnaLeida+=1;
	}

	this->ubicacion = new Coordenadas (longitud, latitud);
}

