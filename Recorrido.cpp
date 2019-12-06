/*
 * Recorrido.cpp
 *
 *  Created on: 5 dic. 2019
 *      Author: David
 */
#include "Recorrido.h"
#include "Estacion.h"

Recorrido::Recorrido(){

	this->primerEstacion = NULL;
	this->distacia = 0;
	this->cursorRecorrer = NULL;
	this->cantidadDeEstaciones = 0;

}

void Recorrido::agregarAlPrincipio(Estacion* nuevaEstacion){
	Nodo<Estacion*>* nuevo = new Nodo<Estacion*>(nuevaEstacion);

	if(this->estaVacio()){
			this->primerEstacion = nuevo;
			this->cantidadDeEstaciones++;
	}else{
		Nodo<Estacion*>* siguiente = this->primerEstacion;
		this->primerEstacion = nuevo;
		nuevo->cambiarSiguiente(siguiente);
		this->distacia = distacia + this->primerEstacion->obtenerDato()->verUbicacion().distanciaMetros(siguiente->obtenerDato()->verUbicacion());
		this->cantidadDeEstaciones++;
	}


}

void Recorrido::agregarAlFinal(Estacion* nuevaEstacion){

	Nodo<Estacion*>* nuevo = new Nodo<Estacion*>(nuevaEstacion);
	Nodo<Estacion*>* recorrer = this->primerEstacion;
	if(this->estaVacio()){
		this->primerEstacion = nuevo;
		this->cantidadDeEstaciones++;
	}else{
		while(recorrer->obtenerSiguiente() != NULL){
			recorrer = recorrer->obtenerSiguiente();
		}
		recorrer->cambiarSiguiente(nuevo);
		this->distacia =this->distacia + recorrer->obtenerDato()->verUbicacion().distanciaMetros(nuevaEstacion->verUbicacion());
		this->cantidadDeEstaciones++;
	}
}

float Recorrido::obtenerDistancia(){
	return this->distacia;
}

unsigned int Recorrido::obtenerCantidadDeEstaciones(){
		return this->cantidadDeEstaciones;
	}

bool Recorrido::estaVacio(){
	if(this->primerEstacion == NULL){
		return true;
	}else{
		return false;
	}
}

void Recorrido::iniciarRecorrido(){
	this->cursorRecorrer = NULL;
}

bool Recorrido::avanzarRecorrido(){
	if(this->cursorRecorrer == NULL){
		this->cursorRecorrer = this->primerEstacion;
	}else{
		this->cursorRecorrer = this->cursorRecorrer->obtenerSiguiente();
	}

	return (this->cursorRecorrer != NULL);
}

Estacion* Recorrido::obtenerRecorrido(){
	Estacion* recorrido;

	if(this->cursorRecorrer != NULL){
		recorrido = this->cursorRecorrer->obtenerDato();
	}

	return recorrido;

}

bool Recorrido::operator <=(Recorrido* otroRecorrido){

	if(this->obtenerDistancia() <= otroRecorrido->obtenerDistancia()){
		return true;
	}else{
		return false;
	}
}

void Recorrido:: operator =(Recorrido* otroRecorrido){
	while(this->primerEstacion != NULL){
		Nodo<Estacion*>* aBorrar = this->primerEstacion;
		this->primerEstacion = this->primerEstacion->obtenerSiguiente();
		delete aBorrar;
	}
	otroRecorrido->iniciarRecorrido();
	while(otroRecorrido->avanzarRecorrido()){
		this->agregarAlFinal(otroRecorrido->obtenerRecorrido());
	}

}


Recorrido::~Recorrido(){

	while(this->primerEstacion != NULL){
		Nodo<Estacion*>* aBorrar = this->primerEstacion;
		this->primerEstacion = this->primerEstacion->obtenerSiguiente();
		delete aBorrar;
	}
}





