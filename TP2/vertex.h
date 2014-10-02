/*! \file vertex.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _VERTEX_H
#define _VERTEX_H

#include "base.h"


/*! Dimension de l'espace */
#define DIM 2

/*! enum pour representer l'orientation de trois points*/
typedef enum
{
	GAUCHE = -1, 
	ALIGNES = 0, 
	DROITE = 1
}Orientation;

/*! enum pour la position du point par rapport a un polygone*/
typedef enum
{
	DEDANS = -1,
	DESSUS = 0,
	DEHORS = 1,
	POLYGONE = 2
} Position;

/*! Structure pour representer un point. */
typedef struct
{
	double coords[DIM];
	Position position;
} vertex;

#endif