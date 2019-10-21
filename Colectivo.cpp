
#include "Colectivo.h"


Colectivo::Colectivo(std::string datos){
    this->leerInformacion(datos);
}

void Colectivo::leerInformacion(std::string datos){
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
					latitud=dato;
					}break;
				
                case 2:{
					longitud=dato;
					}break;

				case 8:{
					this->linea=dato;
					}break;
				}
				columnaLeida+=1;
		}

		this->ubicacion=new Coordenadas(longitud, latitud);
    
}
