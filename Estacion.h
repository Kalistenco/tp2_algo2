/*
 * Estacion.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_ESTACION_H_
#define SRC_ESTACION_H_
#include <string>
#include <fstream>
#include <sstream>
class Estacion {
private:
	typedef unsigned int ui;
	std::string nombre,linea, calle, altura, barrio,destino,
	lineasCombinacionSubte, interseccion, sentido,lineasSentNorte,lineasSentSur;
	std::string longitud, latitud;
	std::string id;
private:
	void leerInformacionSubte(std::string informacion);
	void leerInformacionFerrocarril(std::string informacion);
	void leerInformacionMetrobus(std::string informacion);
public:

	Estacion(std::string informacionEstacion, std::string tipoTransporte);

	std::string verCoordenadaLongitud(){
		return this->longitud;
	}
	std::string verCoordenadaLatitud(){
		return this->latitud;
	}
	std::string verId(){
		return this->id;
	}

	std::string verLinea(){
		return this->linea;
	}
	std::string verCalle(){
		return this->calle;
	}
	std::string verAltura(){
		return this->altura;
	}

	std::string verUbicacion(){
		return this->barrio;
	}

	~Estacion(){

	}
};

#endif /* SRC_ESTACION_H_ */
