/*
 * Estacion.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#include "Estacion.h"

/*Esto es horrible por la comparacion, pero no se me ocurre otra forma sin crear una
 * clase metrobus-ferrocarril-subte etc.*/
Estacion::Estacion(std::string informacionEstacion, std::string tipoTransporte){

	if(tipoTransporte=="ferrocarril"){
		this->leerInformacionFerrocarril(informacionEstacion);
	}else if(tipoTransporte=="subte"){
		this->leerInformacionSubte(informacionEstacion);
	}else if(tipoTransporte=="metrobus"){
		this->leerInformacionMetrobus(informacionEstacion);
	}
}
void Estacion::leerInformacionSubte(std::string informacion){
	std::stringstream registro;
	std::string dato;
	registro<<informacion;
	ui columnaLeida=1;
	while(getline(registro,dato,',')){
				switch(columnaLeida){
				case 1:{
					this->longitud=dato;
				}break;
				case 2:{
					this->latitud=dato;
				}break;
				case 3:{
					this->id=dato;
				}break;
				case 4:{
					this->linea=dato;
				}break;
				case 5:{
					this->nombre=dato;
				}break;
				case 7:{
					this->destino=dato;
				}break;
				case 8:{
					this->lineasCombinacionSubte=dato;
				}break;
				case 15:{
					this->calle=dato;
				}break;
				case 16:{
					this->altura=dato;
				}break;
			}
				columnaLeida+=1;
		}
}
void Estacion::leerInformacionFerrocarril(std::string informacion){
	std::stringstream registro;
	std::string dato;
	registro<<informacion;
	ui columnaLeida=1;
	while(getline(registro,dato,',')){
		switch(columnaLeida){
			case 1:{
				this->longitud=dato;
			}break;
			case 2:{
				this->latitud=dato;
			}break;
			case 3:{
				this->id=dato;
			}break;
			case 4:{
				this->nombre=dato;
			}break;
			case 5:{
				this->linea=dato;
			}break;
			}
		columnaLeida+=1;
	}
}
void Estacion::leerInformacionMetrobus(std::string informacion){
	std::stringstream registro;
	std::string dato;
	registro<<informacion;
	ui columnaLeida=1;
		while(getline(registro,dato,',')){
				switch(columnaLeida){
				case 1:{
					this->longitud=dato;
				}break;
				case 2:{
					this->latitud=dato;
				}break;
				case 3:{
					this->id=dato;
				}break;
				case 4:{
					this->nombre=dato;
				}break;
				case 5:{
					this->calle=dato;
				}break;
				case 7:{
					this->interseccion=dato;
				}break;
				case 8:{
					this->lineasSentNorte=dato;
				}break;
				case 9:{
					this->lineasSentSur=dato;
				}break;
				case 11:{
					this->sentido=dato;
				}break;
			}
				columnaLeida+=1;
		}
}
/*agregar campos que faltan y son importantes en leerInformacion...()*/

