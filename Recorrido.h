/*
 * Recorrido.h
 *
 *  Created on: 5 dic. 2019
 *      Author: David
 */

#ifndef RECORRIDO_H_
#define RECORRIDO_H_
#include"Estacion.h"
//#include"Lista.h"
#include"Nodo.h"
class Recorrido{

private:

	Nodo<Estacion*> *primerEstacion;
	float distacia;
	Nodo<Estacion*> *cursorRecorrer;
	unsigned int cantidadDeEstaciones;

public:

	Recorrido();

	/*agrega estacione al final del recororrido*/
	void agregarAlFinal(Estacion* nuevaEstacion);

	void agregarAlPrincipio(Estacion* nuevaEstacion);

	float obtenerDistancia();

	bool estaVacio();

	unsigned int obtenerCantidadDeEstaciones();

	void iniciarRecorrido();

	bool avanzarRecorrido();

	Estacion* obtenerRecorrido();
	void leerRecorrido(){

		this->iniciarRecorrido();
		while(this->avanzarRecorrido()){
			Estacion* parada=this->obtenerRecorrido();
			std::cout<<" | "<<parada->verTipoTransporte()<< " | "
					<<parada->verLinea()<<" | "<<" | "<<parada->verNombre()
					<<" | "<<parada->verUbicacionLatitud()<<" | "<<parada->verUbicacionLongitud()<<" | "<<std::endl;
		}
	}

	bool operator < (Recorrido* otroRecorrido);

	void operator =(Recorrido* otroRecorrido);


	~Recorrido();


};




#endif /* RECORRIDO_H_ */
