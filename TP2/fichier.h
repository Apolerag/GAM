/*! \file fichier.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _FICHIER_H
#define _FICHIER_H

#include "base.h"
#include "polygone.h"

#include <stdio.h>
#include <stdlib.h>


/*! contient le nom du fichier à lire*/
extern char *in;

/*! contient le nom du fichier à écrire*/
extern char *out;

/*! lit un fichier contenant une liste de point formant un polygone*/
void lireFichier(const char *fichier, polygone *P);

/*! ecrit un fichier contenant une liste de point formant un polygone*/
void ecrireFichier(const char *fichier, const polygone *P);

#endif
