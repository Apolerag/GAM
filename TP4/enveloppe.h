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
void enleveDernierElement(enveloppe *e);

/*! échange les positions de deux vertices dans la liste
* \arg v1, v2 les vertices à échanger
*/
void permuteElement(vertex *v1, vertex *v2);

// coupe la liste en 2 listes en prenant un terme sur deux
vertex* Separer(vertex *liste);

vertex* fusion(vertex *lg,vertex *ld, const vertex* origin);

void afficherListe(vertex *v);

void Trier(vertex* l, const vertex* origin);

/*! calcul de l'enveloppe convexe des vertices en utilisant un algorithme "naif"
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void enveloppeConvexeBrut(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode de Jarvis
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void jarvis(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode de Graham
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void graham(vertex *v, enveloppe *e, const int nb);

#endif
