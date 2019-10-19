#ifndef SUBTE_H_
#define SUBTE_H_

#include <iostream>
#include "Coordenadas.h"

class Subte{
    private:
        Coordenadas ubicacion;
        std::string id, linea, estacion, destino, combinaciones, calle, altura;

        void leerInformacion(std::string datos);

    public:
        Subte(std::string datos);

        ~Subte(){}
};

#endif