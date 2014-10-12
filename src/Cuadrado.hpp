#ifndef H_CUADRADO
#define H_CUADRADO

#include <stdexcept>

enum error_cuadrado{MAL_PARAMETRO};

class Cuadrado
{
	private:
		int posx, posy, largo; 
		int area;
	
	public:
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
};

#endif
