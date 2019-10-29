#ifndef SUBTE_H_
#define SUBTE_H_

#include "Coordenadas.h"

class Subte{
    private:
        Coordenadas *ubicacion;
        std::string id, linea, estacion, destino, combinaciones, calle, altura;

        void leerInformacion(std::string datos);

    public:
        Subte(std::string datos);
        float verUbicacionLatitud(){
           	return this->ubicacion->verLatitud();
        }
        float verUbicacionLongitud(){
           	return this->ubicacion->verLongitud();
        }
        ~Subte(){
        	delete this->ubicacion;
        }
};

#endif
