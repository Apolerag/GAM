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

void ajoutePoint(polygone *p, const vertex v)
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

rectangleEnglobant rectangleEnglobantPolygone(const vertex *v,const int nb)
{
	rectangleEnglobant r;
	r.Xmax = r.Xmin = v[0].coords[0];
	r.Ymax = r.Ymin = v[0].coords[1];
	int i;
	for(i = 1; i < nb; i++)
	{
		if(r.Xmax < v[i].coords[0]) r.Xmax = v[i].coords[0];
		if(r.Xmin > v[i].coords[0]) r.Xmin = v[i].coords[0];
		if(r.Ymax < v[i].coords[1]) r.Ymax = v[i].coords[1];
		if(r.Ymin > v[i].coords[1]) r.Ymin = v[i].coords[1];
	}
	return r;
}
