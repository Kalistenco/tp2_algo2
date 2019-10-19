/*
 * Archivo.h
 *
 *  Created on: 13 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_ARCHIVO_H_
#define SRC_ARCHIVO_H_

#include <string>
#include "Lista.h"

class Archivo {
	
	std::string linkArchivo;

	public:

		/*post:referencia a un archivo relativo*/
		Archivo(std::string linkArchivoRelativo);

		/*pre:referencia existente de archivo, objeto declarado.
		 *post:referencia a lista en memoria con un elemento por linea leida*/
		Lista<std::string>* leerArchivo();

		~Archivo(){};	
};

#endif /* SRC_ARCHIVO_H_ */
