/*! \file file_prioriteInt.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef FILE_PRIORITEINT_H
#define FILE_PRIORITEINT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct{
   int *file; 			/*!gestion dynamique de la mémoir occupée*/
   unsigned int nbElem;	/*!nombre d'éléments de la file*/
   unsigned int nbMax;	/*!nombre max d'éléments de la file*/
} file;

/*! initialise la file par defaut*/
void initialiserFileDefautInt(file *f);

/*! initialise la file avec une taille donnée par l'utilisateur*/
void initialiserFileInt(file *f, const unsigned int taille);

/*! libere la place mémoire occupé par la file*/
void freeFileInt(file *f);

/*! insere l'élément n dans la file, celle ci est retriée automatiquement*/
void insererFileInt(file *f, const int n);

/*! affiche le contenu de la file*/
void afficherFileInt(file *f);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
int recupereElement(file *f);

/*! échange le contenu des cases i et j de la file*/
void echangeCase(file *f, const unsigned int i, const unsigned int j);

#endif
