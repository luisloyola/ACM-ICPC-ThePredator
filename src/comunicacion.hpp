#include <list>
#include "Area.hpp"
#include "Cuadrado.hpp" 

/**
 * Envia una lista de cuadrados al proceso `pid'
 *
 * @param lista	Lista que se envia
 * @param pid	Proceso al cual se envia
 */
void send(list<Cuadrado> &lista, int pid);

/**
 * Envia una lista de areas al proceso `pid' 
 *
 * @param lista	Lista que se envia
 * @param pid	Proceso al cual se envia
 */
void send(list<Area> &lista, int pid);

/**
 * Envia una lista de predadores al proceso `pid' 
 *
 * @param lista	Lista que se envia
 * @param pid	Proceso al cual se envia
 */
void send(list<Predator> &lista, int pid);

/**
 * Recolecta datos de multiples procesos en uno solo. Sigue la misma idea de 
 * 'MPI::COMM_WORLD.Gather()' el cual recolecta informacion de todos los 
 * procesos en uno solo, con la diferencia que 'Gather' hace tambien el trabajo 
 * de union entre esos datos que recibe con los propios.
 *
 * @param lista		Es la lista que se comparte, digamos un: «L sub i». Y a la 
 * vez es la lista del proceso receptor donde se agregan los datos recibidos.
 * @param recp_pid	El pid del proceso receptor.
 */
void Gather(list<Area> &lista, int recp_pid);

/**
 * Hace broadcast de la lista de predadores. El algoritmo es el mas basico e 
 * ineficiente, de orden O(P*l): donde «P» es la cantidad de procesadores y «l» 
 * es el numero de predadores en la lista.
 *
 * @param lista	La lista que se comparte
 * @param root	El proceso que comparte
 */
void Bcast(list<Predator> &lista, int root);

/**
 * Hace broadcast de la lista de cuadrados
 *
 * @param lista	La lista que se comparte
 * @param root	El proceso que comparte
 */
void Bcast(list<Cuadrado> &lista, int root);
