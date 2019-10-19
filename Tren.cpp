#include <iostream>
#include <sstream>
#include "Tren.h"

Tren::Tren(std::string datos){  
    this->leerInformacion(datos);
}

void Tren::leerInformacion(std::string datos){
    std::stringstream registro;
	std::string dato;
    std::string longitud, latitud;
	registro<<datos;
	unsigned int columnaLeida=1;

	while(getline(registro,dato,',')){
		switch(columnaLeida){
			case 1:{
				longitud=dato;
			}break;

			case 2:{
				latitud=dato;
			}break;

			case 3:{
				this->id=dato;
			}break;

			case 7:{
				this->ramal=dato;
			}break;
        }

		columnaLeida++;
    }


    this->ubicacion = Coordenadas(longitud, latitud);

}