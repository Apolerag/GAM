#ifndef _FILE_PRIORITE_INT_H
#define _FILE_PRIORITE_INT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct{
   int *file; 			/*gestion dynamique de la mémoir occupée*/
   unsigned int nbElem;	/*nombre d'éléments de la file*/
   unsigned int nbMax;	/*nombre max d'éléments de la file*/
} file;

/*! initialise la file par defaut*/
void initialiser_file_defaut_int(file *f);

/*! initialise la file avec une taille donnée par l'utilisateur*/
void initialiser_file_int(file *f, const unsigned int taille);

/*! libere la place mémoire occupé par la file*/
void free_file_int(file *f);

/*! insere l'élément n dans la file, celle ci est retriée automatiquement*/
void inserer_file_int(file *f, const int n);

/*! affiche le contenu de la file*/
void afficher_file_int(file *f);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
int recupere_element(file *f);

/*! échange le contenu des cases i et j de la file*/
void echange_case(file *f, const unsigned int i, const unsigned int j);

#endif
