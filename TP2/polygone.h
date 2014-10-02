/*! \file polygone.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _POLYGONE_H
#define _POLYGONE_H

#include "base.h"
#include "vertex.h"
	

/*! enum pour le sens de rotation du polygone*/
typedef enum
{
  TRIGONOMETRIQUE = 0,
  HORAIRE = 1
} Sens;

/*! structure polygone contenant un tableau de vertex et le nombre de vertex de ce tableau*/
typedef struct 
{
	vertex *p;
	unsigned int nbVertex;
	unsigned int nbOccupe;
} polygone;

/*!	initialise le polygone avec un tableau de vertex de taille taille;
* /arg	p le polygone a initialiser
* /arg taille la taille du nombre de sommet
*/
void initialisePolygone(polygone *p, const int taille);

/*! libere la place occupé en mémoire par le polygone
*/
void videPolygone(polygone *p);

/*!
* insere un point dans le polygone
*/
void ajoutePoint(polygone *p, vertex v);

#endif
