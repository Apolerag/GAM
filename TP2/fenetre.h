/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _FENETRE_H
#define _FENETRE_H

#include "polygone.h"

#include <unistd.h>  
#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>

/*! Tailles diverses du systemes de fenetrage .*/
typedef struct {
	double minX;
	double maxX;
	double minY;
	double maxY;
	double margin;
} fenetre;

/*! la fenêtre qui est affichée*/
fenetre f;

/*! le polygone à dessiner */
polygone P;

/*!
* donne une valeur au polygone
*/
void assigneValeurPolygone(polygone *m);

/*! modifie la dimension de la fenetre
* \arg X_min, X_max, Y_min, Y_max, margin les nouvelles dimensions de la fenetre
*/
void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin);

/*! vide la fenetre
*
*/
void clearFenetre();

/*! Generation d'un nombre aleatoire entre deux bornes.
* \arg a : borne inferieure
* \arg b : borne superieure.
* \warning verifier que random() retourne bien un entier long entre 0 et RAND_MAX inclus.
*/
double myRandom (const double a, const double b);

/*! Incantation d'ouverture de fenetre OpenGL */
void winInit();

/*! Generations des sites */
void selectPoints (polygone *P);

/*! Affichage.
*\warning Particularite: "callback function", ie pas d'argument transmis
*/
void display();

/*! affiche les points au fur et à mesure que l'on clique sur la fenêtre
* \warning Particularite: "callback function", ie pas d'argument transmis
*/
void displayPoint();

/*! affiche les points d'un polygone
* \warning Particularite: "callback function", ie pas d'argument transmis
*/
void displayPolygone();

/*!
	récupere les coordonnées du point cliqué
*/
void coordonnesPoint(int button, int state, int x, int y);

#endif