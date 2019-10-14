/*
 * Archivo.h
 *
 *  Created on: 13 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_ARCHIVO_H_

#define SRC_ARCHIVO_H_
#include <string>
#include <fstream>
#include "Lista.h"
class Archivo {
	std::string linkArchivo;
public:
	/*post:referencia a un archivo relativo*/
	Archivo(std::string linkArchivoRelativo){
		std::ifstream archivo(linkArchivoRelativo.c_str());
		if(archivo.good()){
			this->linkArchivo=linkArchivoRelativo;
		}
		else{
			throw std::string ("Ruta invalida ");
		}

	}
	/*pre:referencia existente de archivo, objeto declarado.
	 * post:referencia a lista en memoria con un elemento por linea leida*/
	Lista<std::string>* leerArchivo(){
		Lista<std::string> *listaDeRegistros=new Lista<std::string>;
		std::ifstream archivo(linkArchivo.c_str());
		while(!archivo.eof()){
			std::string lineaVacia;
			getline(archivo, lineaVacia);
			listaDeRegistros->agregar(lineaVacia);
		}
		return listaDeRegistros;
	}

	~Archivo(){

	}
};

#endif /* SRC_ARCHIVO_H_ */
