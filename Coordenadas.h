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

        float distanciaMetros(Coordenadas punto2){
            float latitud = this->latitud;
            float longitud = this->longitud;

            //convertir coordenadas a radianes
            latitud = this->latitud * (PI/180);
            longitud = this->longitud * (PI/180);
            punto2.latitud = punto2.latitud * (PI/180);
            punto2.longitud = punto2.longitud * (PI/180);

            return RADIO_TIERRA * acos(sin(latitud) * sin(punto2.latitud) 
                + cos(latitud) * cos(punto2.latitud) * cos (longitud - punto2.longitud)) * 1000;
        }
        
        float verLongitud(){
        	return this->longitud;
        }
        
        float verLatitud(){
            return this->latitud;
        }

        void setLatitud(float nuevaLatitud);

        void setLongitud(float nuevaLongitud);


        ~Coordenadas(){
        };
};

#endif
