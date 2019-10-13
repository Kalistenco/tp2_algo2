#include <iostream>

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

        float distanciaMetros(float latitud, float longitud){
            
        }

        ~Coordenadas();
}