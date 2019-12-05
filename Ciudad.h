/*
 * Ciudad.h
 *
 *  Created on: 14 oct. 2019
 *      Author: cristian
 */

#ifndef SRC_CIUDAD_H_
#define SRC_CIUDAD_H_
#define DISTANCIA_MAX 500

#include "Estacion.h"
#include "Archivo.h"
#include  "util.h"
#include "Coordenadas.h"

class Ciudad {

	private:
		Lista<Estacion*>*estacionesTren;
		Lista<Estacion*>*bocasSubte;
		Lista<Estacion*>*estacionesColectivo;
		Lista<Estacion*>paradasColectivoAux;
	private:
		bool hayCombinacion(Estacion *intermedia, Coordenadas llegada,
				Lista<Estacion*>*recorridoIntermedio, Lista<Estacion*>*estacionesLlegada);
		void buscarEstacionIntermedia(Lista<Estacion*>*estaciones, Estacion*partida, Coordenadas puntoLlegada,
				Lista<Estacion*>*recorridoIntermedio, Lista<Estacion*>*estacionesLlegada);
		void cargarAdyacentesPorMedioTransporte(Lista<Estacion*>*medioTransporte,
				Estacion* estacionAbuscarAdyacencia);

		void obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,
			Lista<Estacion*>*estacionesCercanas, Estacion* intermedia);

		void borrarDatos(Lista<Estacion*>* medioDeTransporte);
		void cargarEstacionesCercanas(Lista<Estacion*>* medioDeTransporte,
			Lista<Estacion*>* datosCargados, Coordenadas ubicacion);

		void vincularPartidaLlegada(Lista<Estacion*> * estacionesPartida, Lista<Estacion*> * estacionesLlegada
				,Lista<Estacion*>*recorrido);

		/*post: Imprime algunos campos de Lista<Estacion*> *recorrido
		 * por ej: tipo de transporte|linea/ramal que corresponde|
		 * nombre de parada/estacion|coordenadas geograficas.*/

		void leerRecorrido(Lista<Estacion*>*recorrido);
		/*post: agrega en estacionesCercanas las estaciones/paradas con un rango de 250m a la ubicacionUsuario
		 * como pueden ser bocas de subte, paradas de colectivo, estaciones de tren.. */
		void obtenerEstacionesCercanas (Coordenadas ubicacionUsuario,Lista<Estacion*>*estacionesCercanas);


		unsigned int verDistancia(Lista<Estacion*>*recorrido);
		void cargarAdyacentes();
	public:
		/*post: crea ciudad con datos de transportes de archivos csv
		 */
		Ciudad();


		const Lista<Estacion*>*verEstacionesTren(){
			return this->estacionesTren;
		}
		const Lista<Estacion*>* verBocasSubte(){
			return this->bocasSubte;
		}
		const Lista<Estacion*>* verColectivos(){
			return this->estacionesColectivo;
		}

		void cargarDatos (Lista<Estacion*> * medioDeTransporte, Lista<std::string> datos, std::string tipoDeTransporte);
		/*pre: Coordenadas geograficas de caba
		 * post:imprime si existe un recorrido directo entre las coordenadas pedidas,
		 *  si no existe busca e imprime un recorrido con combinacion*/
		void verRecorridoConCombinacion (Coordenadas puntoPartida, Coordenadas puntoLlegada);
		/*pre: coordenadas geograficas no vacias y de caba
		 * post: busca e imprime un posible camino entre esos puntos cuando solamente los une un medio de transporte
		 * */
		void verRecorridoDirecto (Coordenadas puntoPartida, Coordenadas puntoLlegada);


		~Ciudad();
};

#endif /* SRC_CIUDAD_H_ */
