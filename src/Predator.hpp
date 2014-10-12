#ifndef H_PREDATOR
#define H_PREDATOR

#include <stdexcept>

enum error_predator{MAL_PARAMETRO2};

class Predator
{
	private:
		int posx, posy;
	
	public:

		Predator(int x, int y);
};

#endif
