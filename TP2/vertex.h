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
} Orientation;

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

/*! Calcul le determinant de la matrice 3*3 abcdefghi
* \arg a, b, c la premiere ligne de la matrice
* \arg c, d, e la deuxieme ligne de la matrice
* \arg g, h, i la troisieme ligne de la matrice
*/
double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i);


/*! Calcul l'orientation polaire des Vertex A, B et C
* \arg A, B et C les trois Vertices dont on veut calculer l'angle
* \return l'orientation du vertex C par rapport x
*/
Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C);

/*! Compare les valeur de deux vertices
* \arg A et B deux vertices
* \return 1 si les vertices sont identiques, 0 sinon
*/
int memeVertex(const vertex *A, const vertex *B);

/*!
* \arg A et B deux vertices
* \return le vertex qui est le plus petit dans l'ordre lexicographique
*/
vertex minimum(const vertex *A, const vertex *B);

/*! Retourne l'indice du min lexicographique des points du fichier
* \arg const vertex *v un tableau de vertex
* \arg const int taile la taille du tableau
*/
int minLexicographique(const vertex *v, const int taille);

/*! Calcul la position d'un vertices par rapport à un triangle
* \arg A,B,C le triangle
* \arg N le point 
* \return la position
*/
Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N);

#endif
