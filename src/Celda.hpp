#ifndef H_CELDA
#define H_CELDA

class Celda
{
	private:
		bool visitada;
		bool contiene_predador;
		int altura;
	public:
		
		//Celda(int a);
		
		/**
		 * Aumenta la altura de la celda en 1.
		 */
		void aumentar();
		
		/**
		 * Setea la altura de la celda
		 * @param a Altura
		 */
		 void setAltura(int a);
		 
		 /**
		  * Retorna la altura de la celda
		  * @return altura
		  */
		 int getAltura();
};
#endif
