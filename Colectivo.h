#ifndef COLECTIVO__H
#define COLECTIVO__H

#include "Coordenadas.h"

class Colectivo{
    private:
        Coordenadas *ubicacion;
        std::string linea;

        void leerInformacion(std::string datos);

    public:
        Colectivo (std::string datos);
        std::string verLinea(){
        	return this->linea;
        }
        float verUbicacionLatitud(){
        	return this->ubicacion->verLatitud();
        }
        float verUbicacionLongitud(){
               	return this->ubicacion->verLongitud();
        }

        ~Colectivo(){
        	delete this->ubicacion;
        }
};

#endif
