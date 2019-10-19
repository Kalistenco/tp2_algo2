#ifndef COLECTIVO__H
#define COLECTIVO__H

#include <iostream>
#include "Coordenadas.h"

class Colectivo{
    private:
        Coordenadas ubicacion;
        std::string linea;

        void leerInformacion(std::string datos);

    public:
        Colectivo (std::string datos);
};

#endif