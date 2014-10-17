#ifndef H_AREA
#define H_AREA

#include "Celda.hpp"
#include "Predator.hpp"
#include <list>

using namespace std;

class Area
{
	private:

		int area_val;						//!< Cuantas celdas que tiene el area
		list<Celda> superiores, inferiores;	//!< ? posible futura clase


	public:
		bool contiene_predator;				//!< Indica si el predador esta en el area

		/**
		 * Constructor
		 */
		Area();

		/**
		 * Indica si es adyacente con otra area o no
		 *
		 * @param otra	Es el area que se comprueba si es adyacente a esta.
		 *
		 * @return «true» si `otra' es adyacente y «false» en otro caso.
		 */
		bool es_adyacente(Area& otra);

		/**
		 * Agrega un cuadrado a la lista de cuadrados superior
		 *
		 * @param nuevo
		 */
		void add_celda_sup(int celda_x, int celda_y);

		/**
		 * Agrega un cuadrado a la lista de cuadrados inferior
		 *
		 * @param nuevo
		 */
		void add_celda_inf(int celda_x, int celda_y);

		void add_celda_sup2(const Celda &ce);
		void add_celda_inf2(const Celda &ce);

		void setArea(int a);
		int getArea();
		list<Celda> get_sup();
		list<Celda> get_inf();
		int recorrerArea(int i, int j, Celda** matrix, int nfilas, int ncolumnas, int valor_predator, Predator pred);

};

#endif
