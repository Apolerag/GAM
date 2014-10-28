/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <assert.h>
#include "fenetre.h"

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin)
{
	f.minX = X_min;
	f.maxX = X_max;
	f.minY = Y_min;
	f.maxY = Y_max;
	f.margin = margin;
}

void clearFenetre(vertex *v, int nb)
{
	free(v);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

double myRandom (double a, double b)
{
	double tmp = random(); /* long int in [0, RAND_MAX] */

	return a+tmp*((b-a)/RAND_MAX);
}

void selectPoints (vertex *v, const int nb)
{
	int n = nb;
	/*if(!(f.maxX - f.minX > 200)) exit(-1);
	if(!(f.maxY - f.minY > 200)) exit(-1);*/
	while (--n >= 0)
	{	
		v[n].coords[0] = myRandom(f.minX + 100, f.maxX-100);
		v[n].coords[1] = myRandom(f.minY + 100, f.maxY-100);
	}
		
//	displayPoint(v,nb);
}

void effaceFenetre()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void displayEnveloppe(const enveloppe *e)
{
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);

	vertex *j = e->premier;
	do
	{
		glVertex2f(j->coords[0],f.maxY - j->coords[1]);
		printf("%lf %lf\n",j->coords[0],j->coords[1]);
		j = j->suivant;
	}
	while(j != e->premier);
	glEnd();

}

void displayPoints(const vertex *v, const int nb)
{
	int i;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	for (i = 0; i < nb; ++i)
	{
		glVertex2f(v[i].coords[0], f.maxY - v[i].coords[1]);
	}
	glEnd();
}
