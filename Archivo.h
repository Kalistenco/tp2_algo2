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

		/*pre:referencia existente de archivo, objeto declarado,
		 *  Lista por referencia para la carga
		 * de registros.
		 *post:referencia a lista con los registros.
		 * Un registro por espacio de lista.
		 * ej de registro: LONGITUD-LATITUD-LINEA-NOMBRE-ID-... */
		void leerArchivo(Lista<std::string> &listaVacia );

		~Archivo(){};	
};

#endif /* SRC_ARCHIVO_H_ */
