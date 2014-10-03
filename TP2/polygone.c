#include "polygone.h"

#include <stdio.h>
#include <stdlib.h>

void initialisePolygone(polygone *p, const int taille)
{
	p->nbVertex = taille;
	ALLOUER(p->p, taille);
	p->nbOccupe = 0;
}

void videPolygone(polygone *p)
{
	free(p->p);
}

void ajoutePoint(polygone *p, vertex v)
{
	if(p->nbVertex == p->nbOccupe)
	{
		vertex *tamp;
		int i;
		tamp = p->p;
		ALLOUER(p->p, p->nbVertex*2);
		p->nbVertex *=2;

		for(i =0; i<p->nbOccupe; i++)
		{
			p->p[i] = tamp[i];
		}
		free(tamp);
	}

	p->p[p->nbOccupe] = v;
	p->nbOccupe ++;

}
