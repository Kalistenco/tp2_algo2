#ifndef COORDENADAS__H
#define COORDENADAS__H

#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

#define PI 3.14159
#define RADIO_TIERRA 6378.1

class Coordenadas {
    private: 
		float latitud;
		float longitud;

        float stringToFloat(const std::string& strToFloat)
          {
        	float valor;
             std::stringstream stream(strToFloat);
             stream >> valor;
             if (stream.fail()) {
            	 valor=0.0;
             }
             return valor;
          }

    public:
        Coordenadas (std::string longitud, std::string latitud){
        	this->latitud=this->stringToFloat(latitud);
        	this->longitud=this->stringToFloat(longitud);

            //this->latitud = strtof(latitud.c_str(), 0);
            //this->longitud = strtof(longitud.c_str(), 0);
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
        float verLongitud(){
        	return this->longitud;
        }
        float verLatitud(){
            return this->latitud;
        }

        ~Coordenadas(){};
};

#endif
