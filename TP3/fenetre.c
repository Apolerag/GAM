/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <assert.h>
#include <time.h>
#include "fenetre.h"

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin)
{
	f.minX = X_min;
	f.maxX = X_max;
	f.minY = Y_min;
	f.maxY = Y_max;
	f.margin = margin;
}

void clearFenetre()
{
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
	assert(f.maxX - f.minX > 200);
	assert(f.maxY - f.minY > 200);
	while (--n >= 0)
	{
		v[n].coords[0] = myRandom(f.minX + 100, f.maxX-100);
		v[n].coords[1] = myRandom(f.minY + 100, f.maxY-100);
	}
	
}


void enveloppeConvexeBrut(const vertex *v, const int nb)
{
	float temps;
    clock_t t1, t2;

	assert(v != NULL);
	assert(nb > 0);
	int min = minLexicographique(v, nb);
	int i, j, k;
	/*int next = 0;*/
	int non = 0;
	int *p;
	int compteur = 0;
	ALLOUER(p, nb);


	/*calcul de l'enveloppe convexe*/


	t1 = clock();
	i = min;

	do
	{
		p[compteur] = i;
		compteur ++;
		 for(j = 0; j < nb; j++)
		 {
		 	if(i != j)
		 	{
		 		non = 0;
		 		for(k = 0; k < nb; k++)
				{
					if(k != j && k!= i)
					{
						if(orientationPolaire(&v[i],&v[j],&v[k]) != GAUCHE)
						{
							non = 1;
							k = nb;
						}
					}
				}
				if(!non)
				{
					i = j;
					j = nb;
				}
		 	}
		 }
	} while (i != min);	
	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

	glColor3f(0.0, 0.0 , 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	/*affichage de l'enveloppe-*/
	for (i = 0; i < compteur; ++i)
	{
		glVertex2f(v[p[i]].coords[0], f.maxY - v[p[i]].coords[1]);
	}
	glEnd();


	/* affichage des points*/
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	for (i = 0; i < nb; ++i)
	{
		glVertex2f(v[i].coords[0], f.maxY - v[i].coords[1]);
	}
	glEnd();

	glFlush();	

	free(p);
}

