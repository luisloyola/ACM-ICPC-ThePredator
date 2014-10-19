#include <list>
#include "Area.hpp"
#include "Cuadrado.hpp"


/**
 * Recibe las areas que fueron enviadas en el SStep anterior y las coloca 
 * dentro de una lista enlazada especificada.
 *
 * @param destino	Es la referencia de la lista en donde se deben agregar las 
 * areas.
 */

void get_areas(std::list<Area> &destino);

/**
 * Recibe los cuadrados que fueron enviados en el SStep anterior y los coloca 
 * dentro de la lista especificada.
 *
 * @param destino	Es la referencia de la lista en donde se deben agregar los 
 * cuadrados.
 */
void get_cuadrados(std::list<Cuadrado> &destino);
