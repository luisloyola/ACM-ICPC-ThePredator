#ifndef H_AREA
#define H_AREA

#include "Celda.hpp"
#include "Predator.hpp"
#include <list>

using namespace std;

class Area
{
	private:

		int area_val;						//!< Cuantas celdas tiene el area
		list<Celda> superiores, inferiores;


	public:
		const static int TAG = 732;
		bool contiene_predator;				//!< Indica si el predador esta en el area

		/**
		 * Constructor
		 */
		Area();

		Area(int valor_inicial);

		/**
		 * Constructor. Setea los valores de esta area a partir de un arreglo 
		 * de enteros que representa el area de la misma forma en la que se 
		 * serializa en la funcion 'send()'
		 *
		 * @param buffer	Arreglo de «int» que trae todos los valores del  
		 * 'Area' y las coordenadas de las celdas pertenecientes a la misma.
		 */
		Area(int* buffer);

		~Area();

		/**
		 * Indica si es adyacente con otra area o no
		 *
		 * @param otra	Es el area que se comprueba si es adyacente a esta.
		 *
		 * @return «true» si `otra' es adyacente y «false» en otro caso.
		 */
		bool es_adyacente(Area& otra);

		/**
		 * Agrega una celda a la lisa de celdas superiores
		 *
		 * @param celda_x	Coordenada x de la celda
		 * @param celda_y	Coordenada y de la celda
		 */
		void add_celda_sup(int celda_x, int celda_y);

		/**
		 * Agrega una celda a la lisa de celdas inferiores
		 *
		 * @param celda_x	Coordenada x de la celda
		 * @param celda_y	Coordenada y de la celda
		 */
		void add_celda_inf(int celda_x, int celda_y);

		void add_celda_sup(const Celda ce);
		void add_celda_inf(const Celda ce);

		void print_celdas_sup();
		void print_celdas_inf();

		void setArea(int a);
		int getArea();
		list<Celda> get_sup();
		list<Celda> get_inf();
		int recorrerArea(int i, int j, Celda** matrix, int nfilas, int ncolumnas, Predator pred);

		/**
		 * Envia el objeto serializado a algun otro procesador. Esta funcion 
		 * serializa el objeto y lo envia al proceso `pid' mediante la funcion 
		 * «MPI::COMM_WORLD.Send()» de MPI.
		 *
		 * Las coordenadas de las celdas son 2 «int», uno al lado del otro, que 
		 * indican la coordenada «x» e «y» de la celda.
		 *
		 * @param pid	Es el numero del procesador al cual se quiere mandar el 
		 * objeto
		 */
		void send(int pid);

};

#endif
