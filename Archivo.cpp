/*
 * Archivo.cpp
 *
 *  Created on: 9 oct. 2019
 *      Author: cristian
 */

#include "Archivo.h"
#include <fstream>
#include "Lista.h"

Archivo::Archivo(std::string linkArchivoRelativo){

	std::ifstream archivo(linkArchivoRelativo.c_str());
	
	if(archivo.good()){
		this->linkArchivo=linkArchivoRelativo;
	}
	else{
		throw std::string ("Ruta invalida ");
	}
}

void Archivo::leerArchivo(Lista<std::string> &listaVacia){

	//Lista<std::string> listaDeRegistros;//=new Lista<std::string>;
    std::ifstream archivo(linkArchivo.c_str());
		
	while(!archivo.eof()){
		std::string lineaVacia;
		getline(archivo, lineaVacia);
		listaVacia.agregar(lineaVacia);
	}
	
	//return &listaDeRegistros;
}
