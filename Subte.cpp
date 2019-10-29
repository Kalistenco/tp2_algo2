#include <sstream>
#include "Subte.h"

Subte::Subte (std::string datos){
    this->leerInformacion(datos);
}

void Subte::leerInformacion(std::string datos){
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
			case 4:{
			this->linea=dato;
			}break;
            case 5:{
			this->estacion=dato;
			}break;
			case 7:{
			this->destino=dato;
			}break;
			case 8:{
			this->combinaciones=dato;
			}break;
				
            case 15:{
					this->calle=dato;
				}break;
				
            case 16:{
					this->altura=dato;
				}break;
			}
				columnaLeida++;
		}

	this->ubicacion=new Coordenadas(longitud, latitud);

}
