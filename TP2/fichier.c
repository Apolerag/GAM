/*! \file fichier.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include "fichier.h"

void lireFichier(const char *fichier, polygone *P)
{
	FILE *f = fopen(fichier,"r");
	
	assert(f != NULL);
	int i;
	fscanf(f,"%u",&P->nbVertex);
	ALLOUER(P->p,P->nbVertex);
	P->nbOccupe = P->nbVertex;
	for(i = 0; i< P->nbVertex; i++)
	{
		fscanf(f,"%lf, %lf",&P->p[i].coords[0], &P->p[i].coords[1]);
	}	

	fclose(f);
}

void ecrireFichier(const char *fichier, const polygone *P)
{
	FILE *f = fopen(fichier,"w");
	
	assert(f != NULL);
	int i;
	fprintf(f,"%u\n",P->nbOccupe);
	for(i = 0; i< P->nbOccupe; i++)
	{
		fprintf(f,"%lf, %lf\n",P->p[i].coords[0], P->p[i].coords[1]);
	}
	fclose(f);
}
