#include <iostream>
#include <string>
#include <sstream>
#include "Colectivo.h"
#include "Coordenadas.h"

Colectivo::Colectivo(std::string datos){
    this->leerInformacion(datos);
}

void Colectivo::leerInformacion(std::string datos){
	std::stringstream registro;
	std::string dato;
	std::string longitud, latitud;
    registro<<datos;
	unsigned int columnaLeida=1;

		while(getline(registro,dato,',')){
				switch(columnaLeida){
				case 4:{
					latitud=dato;
				}break;
				
                case 5:{
					longitud=dato;
				}break;

				case 8:{
					this->linea=dato;
				}break;
			}
				columnaLeida+=1;
		}

    this->ubicacion = Coordenadas (longitud, latitud);
    
}