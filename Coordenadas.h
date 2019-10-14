#ifndef COORDENADAS__H
#define COORDENADAS__H

#include <iostream>
#include <cmath>

#define PI 3.14159
#define RADIO_TIERRA 6378.1

class Coordenadas {
    private: 
        float latitud;
        float longitud;

    public:
        Coordenadas();

        Coordenadas(float latitud, float longitud){
            this->latitud = latitud;
            this->longitud = longitud;
        }

        float distanciaMetros(float & latitudPunto2, float & longitudPunto2){
            //convertir coordenadas a radianes
            this->latitud = this->latitud * (PI/180);
            this->longitud = this->longitud * (PI/180);
            latitudPunto2 = latitudPunto2 * (PI/180);
            longitudPunto2 = longitudPunto2 * (PI/180);

            return RADIO_TIERRA * acos(sin(this->latitud) * sin(latitudPunto2) 
                + cos(this->latitud) * cos(latitudPunto2) * cos (this->longitud - longitudPunto2)) * 1000;
        }

        ~Coordenadas();
}

#endif