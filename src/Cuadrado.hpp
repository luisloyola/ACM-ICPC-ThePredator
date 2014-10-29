#ifndef H_CUADRADO
#define H_CUADRADO

#include <stdexcept>

#include "Predator.hpp"

class Cuadrado
{
	private:
		int posx, posy, largo;
		int area;

	public:
		const static int TAG = 8237236;
		Cuadrado(int x, int y, int largo);

		/**
		 * Indica si una coordenada pertenece al cuadrado o no
		 *
		 * @param x	Es la coordenada «x»
		 * @param y	Es la coordenada «y»
		 *
		 * @return «true» si la coordenada pertenece al cuadrado y «false» en
		 * caso contrario.
		 */
		bool pertenece(int x, int y);

		/**
		 * Indica si el predador especificado `pertenece' al cuadrado. En 
		 * realidad indica si las coordenadas de «pred» estan dentro de los 
		 * limites de las coordenadas del cuadrado.
		 *
		 * @param pred	Es el predador que se quiere checkear
		 *
		 * @return `true' si las coordenadas del predador estan dentro de los 
		 * limites del cuadrado y `false' en caso contrario
		 */
		bool pertenece(Predator &pred);

		/**
		 * Retorna la posición x del cuadrado
		 * @return posx
		 */
		 int getX();

		 /**
		 * Retorna la posición y del cuadrado
		 * @return posy
		 */
		 int getY();

		 /**
		 * Retorna el largo del cuadrado
		 * @return largo
		 */
		 int getLargo();

		 /**
		  * Manda el cuadrado al procesador con el pid `pid'
		  *
		  * @param pid	Numero del procesador al cual se envia.
		  */
		 void send(int pid);
};

#endif
