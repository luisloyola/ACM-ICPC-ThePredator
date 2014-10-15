#ifndef H_CELDA
#define H_CELDA

class Celda
{
	private:
		bool visitada = false;
		bool contiene_predador;
		int altura;
		int posX;
		int posY;
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
		 
		/**
		 * Asigna una posición x e y a la celda
		 *
		 * @param x Valor X (vertical)
		 * @param y Valor Y (horizontal)
		 */
		 void setXY(int x, int y);
		
		/**
		 * Retorna la posición x de la celda
		 * @return posX de la celda.
		 */
		 int getX();
		 
		/**
		 * Retorna la posición y de la celda
		 * @return posY de la celda.
		 */
		 int getY();
		 
		/**
		 * Marca la celda como visitada
		 */
		 void visitar();
		 
		/**
		 * Verifica si la celda ha sido visitada
		 * @return true si fue visitada o false en caso contrario
		 */
		 bool esVisitada();
};
#endif
