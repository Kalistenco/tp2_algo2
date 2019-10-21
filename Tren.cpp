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
	/*lee una fila (registro) y por un numero de columna guarda la informacion.
	 * Para agregar otros campos del archivo colectivos se podria implmentar...
	 * case (columnaCampoBuscado):guardo la variable
	 * */

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

	this->ubicacion=new Coordenadas(longitud, latitud);

}
