#ifndef ENVELOPPE
#define ENVELOPPE

#include "vertex.h"

typedef struct 
{
	vertex *premier;
	vertex *dernier;
} enveloppe;

/*! initialise les pointeurs de l'envellope à NULL
* \arg e une enveloppe
*/
void initialiseEnveloppe(enveloppe *e);

/*! ajoute un vertex à la fin de la liste de vertex de l'enveloppe
* \arg e l'enveloppe
* \arg v le vertex 
*/
void ajouteElement(enveloppe *e, vertex *v);


/*! enleve le dernier vertex de la liste de l'enveloppe
* \arg e l'enveloppe
*/
void enleveElement(enveloppe *e);

/*! calcul de l'enveloppe convexe des vertices en utilisant un algorithme "naif"
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void enveloppeConvexeBrut(vertex *v, enveloppe *e, const int nb);

#endif
