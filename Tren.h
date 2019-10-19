#ifndef TREN_H_
#define TREN_H_

#include <iostream>
#include "Coordenadas.h"

class Tren{
    private:
        Coordenadas ubicacion;
        std::string id, ramal;

        void leerInformacion(std::string datos);

    public:
        Tren(std::string datos);

        void verRamal(){
            std::cout<< this->ramal << std::endl;
        }
};

#endif