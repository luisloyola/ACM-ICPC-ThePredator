#ifndef H_PREDATOR
#define H_PREDATOR

#include <stdexcept>

enum error_predator{MAL_PARAMETRO2};

class Predator
{
	private:
		int posx, posy, altura;

	public:

		const static int TAG = 7733867;
		Predator(int x, int y);

		/**
		 * Retorna la posición x del depredador
		 * @return posx
		 */
		int getX();

		/**
		 * Retorna la posición y del depredador
		 * @return posy
		 */
		int getY();

		/**
		 * Retorna la altura del depredador
		 * @return altura
		 */
		int getAltura();

		/**
		 * Asigna una altura la depredador
		 * @param alt Altura del depredador
		 */
		void setAltura(int alt); 

		void send(int pid);
};

#endif
