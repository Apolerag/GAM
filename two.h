#ifndef __TWO_H__
#define TWO_H__
/*! \file two.h
* \author JM Moreau, A Chemier, R Lhomme
* \date 2004 - 2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  
#include <unistd.h>  
#include <GL/glut.h> 

/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

/*! Dimension de l'espace */
#define DIM 2

/*! enum pour representer l'orientation de trois points*/
typedef enum
{
	GAUCHE = -1, 
	ALIGNES = 0, 
	DROITE = 1
}Orientation;

/*! enum pour la position du point par rapport au triangle*/
typedef enum
{
	DEDANS = -1,
	DESSUS = 0,
	DEHORS = 1,
	TRIANGLE = 2
} Position;

/*! Structure pour representer un point. */
typedef struct
{
	double coords[DIM];
	Position position;
} vertex;

/*! Tailles diverses du systemes de fenetrage .*/
const double minX = 0,
maxX = 500,
minY = 0,
maxY = 500,
margin = 10;

/*! Nombre de "sites" dans le programme, modifiable par la ligne
* de commande de la fonction main().
*/
int nbPoints = 50;

/*! Tableau gobal des sommets */
vertex *T = NULL;

/*! Nombre de vertex dans le fichier lu*/

int nbFic = 0;

/*! Liste des vertices du fichier*/
vertex *L = NULL;

#endif