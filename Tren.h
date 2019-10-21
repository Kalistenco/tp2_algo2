#ifndef TREN_H_
#define TREN_H_
#include <sstream>

#include "Coordenadas.h"

class Tren{
    private:
        Coordenadas *ubicacion;
        std::string id, ramal;

        void leerInformacion(std::string datos);

    public:
        Tren(std::string datos);

        std::string verRamal(){

            /*std::cout<< "ENTRO A VER RAMAL" << std::endl;
            std::cout<< this->ramal << std::endl;*/
        	return this->ramal;
        }
        float verUbicacionLatitud(){
              	return this->ubicacion->verLatitud();
        }
        float verUbicacionLongitud(){
               	return this->ubicacion->verLongitud();
        }
        ~Tren(){
           	delete this->ubicacion;
         }
};

#endif
